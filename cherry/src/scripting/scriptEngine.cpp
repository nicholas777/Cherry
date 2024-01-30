#include "epch.h"
#include "scriptEngine.h"
#include "core/core.h"
#include "scene/assetManager.h"
#include "scene/component.h"

#include <cstring>

extern "C" {
    #include "lua.h"
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace Cherry {

    lua_State* ScriptEngine::m_State = nullptr;
    Scene* ScriptEngine::m_RuntimeScene = nullptr;
    std::vector<ScriptEngine::ScriptClass> ScriptEngine::m_ScriptClasses;
    std::vector<ScriptEngine::ScriptedEntity> ScriptEngine::m_ScriptedEntities;

    Field::Field(lua_State* L, int table, const char* name)
                : m_State(L), m_Table(table), m_Name(name) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, table);
        lua_getfield(L, -1, name);

        CH_INFO(lua_typename(L, lua_type(L, -1)));

        switch (lua_type(L, -1)) {
            case LUA_TNUMBER: m_Type = ScriptFieldType::Number; break;
            case LUA_TBOOLEAN: m_Type = ScriptFieldType::Bool; break;
            case LUA_TSTRING: m_Type = ScriptFieldType::String; break;
            default: m_Type = ScriptFieldType::Unsupported;
        }

        m_Ref = luaL_ref(L, LUA_REGISTRYINDEX);

        lua_pop(L, 1);
    }

    Field::~Field() {
        luaL_unref(m_State, LUA_REGISTRYINDEX, m_Ref);
    }

    void Field::GetData(void* buf, size_t size) {
        if (m_Type == ScriptFieldType::Unsupported) return;

        lua_rawgeti(m_State, LUA_REGISTRYINDEX, m_Table);
        lua_getfield(m_State, -1, m_Name);

        switch (m_Type) {
            case ScriptFieldType::Bool:
                *(bool*)buf = lua_toboolean(m_State, -1);
                break;
            case ScriptFieldType::Number:
                *(double*)buf = lua_tonumber(m_State, -1);
                break;
            case ScriptFieldType::String:
                CH_ASSERT(luaL_len(m_State, -1) <= size, "Buffer too small");
                strncpy((char*)buf, lua_tostring(m_State, -1), luaL_len(m_State, -1));
                break;
            default:
                return;
        }

        lua_pop(m_State, 2);

    }

    void Field::SetData(void* buf) {
        lua_rawgeti(m_State, LUA_REGISTRYINDEX, m_Table);

        switch (m_Type) {
            case ScriptFieldType::Bool:
                lua_pushboolean(m_State, *(bool*)buf);
                break;
            case ScriptFieldType::Number:
                lua_pushnumber(m_State, *(double*)buf);
                break;
            case ScriptFieldType::String:
                lua_pushstring(m_State, (const char*)buf);
                break;
            default: return;
        }

        lua_setfield(m_State, -2, m_Name);
        lua_pop(m_State, 1);
    }

    void ScriptEngine::Init() {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);

        lua_newtable(m_State);
        lua_setglobal(m_State, "__CHERRY_SCRIPTS__");

        lua_pushstring(m_State, CH_VERSION);
        lua_setglobal(m_State, "CH_VERSION");

        // Load scripts
        if (luaL_dofile(m_State, "../cherry/src/lua/cherry.lua") != LUA_OK) {
            CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
            lua_pop(m_State, lua_gettop(m_State));
        }

        // Temporary, we need to move the code that needs this to c land
        luaopen_debug(m_State);

        ReloadScripts();
    }

    void ScriptEngine::Shutdown() {
        lua_close(m_State);
    }

    Scene* ScriptEngine::GetRuntimeScene() {
        return m_RuntimeScene;
    }

    void ScriptEngine::OnRuntimeStart(Scene* scene) {
        m_RuntimeScene = scene;

        for (auto& se : m_ScriptedEntities) {
            if (se.OnCreate == -1) continue;

            lua_rawgeti(m_State, LUA_REGISTRYINDEX, se.OnCreate);

            if (lua_pcall(m_State, 0, 1, 0) != LUA_OK) {
                CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
                lua_pop(m_State, 3);
            }
        }

        lua_pop(m_State, lua_gettop(m_State));
    }

    void ScriptEngine::OnRuntimeStop() {
        m_RuntimeScene = nullptr;

        for (auto& se : m_ScriptedEntities) {
            if (se.OnDestroy == -1) continue;

            lua_rawgeti(m_State, LUA_REGISTRYINDEX, se.OnDestroy);

            if (lua_pcall(m_State, 0, 1, 0) != LUA_OK) {
                CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
                lua_pop(m_State, 3);
            }
        }

        lua_pop(m_State, lua_gettop(m_State));

        m_ScriptedEntities.clear();
    }

    void ScriptEngine::InitScriptedEntity(Entity e) {
        auto& comp = e.GetComponent<ScriptComponent>();

        for (ScriptClass& sc2 : m_ScriptClasses) {
            if (strcmp(sc2.name, comp.Name.c_str()) != 0) 
                continue;

            ScriptedEntity se{};

            lua_rawgeti(m_State, LUA_REGISTRYINDEX, sc2.luaNewMethod);
            lua_createtable(m_State, 0, 2);

            if (lua_pcall(m_State, 1, 1, 0) != LUA_OK) {
                CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
                lua_pop(m_State, lua_gettop(m_State));
                return;
            }

            if (sc2.onCreate) {
                lua_getfield(m_State, -1, "onCreate");
                se.OnCreate = luaL_ref(m_State, LUA_REGISTRYINDEX);
            } 
            if (sc2.onUpdate) {
                lua_getfield(m_State, -1, "onUpdate");
                se.OnUpdate = luaL_ref(m_State, LUA_REGISTRYINDEX);
            } 
            if (sc2.onDestroy) {
                lua_getfield(m_State, -1, "onDestroy");
                se.OnDestroy = luaL_ref(m_State, LUA_REGISTRYINDEX);
            }
            
            se.entity = e;

            se.luaTable = luaL_ref(m_State, LUA_REGISTRYINDEX); 
            lua_getglobal(m_State, "__CHERRY_SCRIPTS__");
            lua_getfield(m_State, -1, sc2.name);

            lua_pushnil(m_State);
            while (lua_next(m_State, -2) != 0) {
                if (!lua_isstring(m_State, -2)) continue;

                const char* name = lua_tostring(m_State, -2);
                if (strcmp(name, "__IS_SCRIPT") == 0) {
                    lua_pop(m_State, 1);
                    continue;
                }

                int type = lua_type(m_State, -1);
                if (type != LUA_TBOOLEAN && type != LUA_TNUMBER && type != LUA_TSTRING) {
                    lua_pop(m_State, 1);
                    continue;
                }

                lua_rawgeti(m_State, LUA_REGISTRYINDEX, se.luaTable);
                lua_pushvalue(m_State, -2);
                lua_setfield(m_State, -2, name);
                
                se.fields.emplace_back(new Field(m_State, se.luaTable, name));

                lua_pop(m_State, 2);
            }

            lua_pop(m_State, lua_gettop(m_State));

            m_ScriptedEntities.push_back(se);
            return;
        }

        CH_ASSERT(false, "No such script class");
    }

    void ScriptEngine::ReloadScripts() {
        auto& scriptAssets = AssetManager::GetScripts();
        for (auto& asset : scriptAssets) {
            if (luaL_dofile(m_State, asset.second.filepath.c_str()) != LUA_OK) {
                CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
                lua_pop(m_State, lua_gettop(m_State));
            }
        }

        lua_getglobal(m_State, "__CHERRY_SCRIPTS__");
        int t = lua_gettop(m_State);
        lua_pushnil(m_State);

        while (lua_next(m_State, t) != 0) {

            if (!lua_isstring(m_State, -2) || !lua_istable(m_State, -1)) {
                lua_pop(m_State, 1);
                continue;
            }

            ScriptClass sc{};

            sc.name = lua_tostring(m_State, -2);
            if (lua_getfield(m_State, -1, "onCreate") != LUA_TNIL && lua_isfunction(m_State, -1)) {
                sc.onCreate = true;
            } 
            lua_pop(m_State, 1);
            
            if (lua_getfield(m_State, -1, "onUpdate") != LUA_TNIL && lua_isfunction(m_State, -1)) {
                sc.onUpdate = true;
            }
            lua_pop(m_State, 1);

            if (lua_getfield(m_State, -1, "onDestroy") != LUA_TNIL && lua_isfunction(m_State, -1)) {
                sc.onUpdate = true;
            }
            lua_pop(m_State, 1);

            if (lua_getfield(m_State, -1, "__new_obj") == LUA_TNIL) {
                lua_pop(m_State, 2);
                continue;
            }

            sc.luaNewMethod = luaL_ref(m_State, LUA_REGISTRYINDEX);
            m_ScriptClasses.push_back(sc);

            lua_pop(m_State, 1);
        }

        lua_pop(m_State, lua_gettop(m_State));
    }

    bool ScriptEngine::IsScriptClass(const std::string& table) {
        for (ScriptClass& sc : m_ScriptClasses) {
            if (strcmp(table.c_str(), sc.name) == 0)
                return true;
        }

        return false;
    }

    std::vector<Shared<Field>>* ScriptEngine::ScriptedEntityGetFields(Entity e) { 
        for (ScriptedEntity& se : m_ScriptedEntities) {
            if ((entt::entity)e != se.entity)
                continue;

            return &se.fields;
        }

        return nullptr;
    }

    void ScriptEngine::UpdateScriptedEntities(float delta) {
        lua_pushglobaltable(m_State);

        for (auto& se : m_ScriptedEntities) {
            if (se.OnUpdate == -1) continue;

            lua_rawgeti(m_State, LUA_REGISTRYINDEX, se.OnUpdate);
            lua_pushnumber(m_State, (lua_Number)delta);

            if (lua_pcall(m_State, 1, 1, 0) != LUA_OK) {
                CH_ERROR(lua_tostring(m_State, lua_gettop(m_State)));
                lua_pop(m_State, 3);
            }
        }

        lua_pop(m_State, lua_gettop(m_State));
    }

}

