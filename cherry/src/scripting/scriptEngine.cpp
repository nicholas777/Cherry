#include "epch.h"
#include "scriptEngine.h"
#include "core/core.h"
#include "lua.h"
#include "scene/assetManager.h"

#include <cstdio>

extern "C" {
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace Cherry {

    lua_State* ScriptEngine::m_State = nullptr;
    Scene* ScriptEngine::m_RuntimeScene = nullptr;

    void ScriptEngine::Init() {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);

        lua_newtable(m_State);
        lua_setglobal(m_State, "__CHERRY_SCRIPTS__");

        lua_pushstring(m_State, CH_VERSION);
        lua_setglobal(m_State, "CH_VERSION");

        // Load scripts
        luaL_dofile(m_State, "../cherry/src/lua/cherry.lua");
        ReloadScripts();
    }

    void ScriptEngine::Shutdown() {
        UnloadScriptedEntities();
        lua_close(m_State);
    }

    void ScriptEngine::RegisterScriptedEntity(const Entity& e) {

    }

    Scene* ScriptEngine::GetRuntimeScene() {
        return m_RuntimeScene;
    }

    void ScriptEngine::OnRuntimeStart(Scene* scene) {
        m_RuntimeScene = scene;
    }

    void ScriptEngine::OnRuntimeStop() {
        m_RuntimeScene = nullptr;
    }

    void ScriptEngine::InitScriptedEntity(Entity e) {}

    void ScriptEngine::ReloadScripts() {
        auto& scriptAssets = AssetManager::GetScripts();
        for (auto& asset : scriptAssets) {
            luaL_dofile(m_State, asset.second.filepath.c_str());
        }

        lua_getglobal(m_State, "__CHERRY_SCRIPTS__");
        int t = lua_gettop(m_State);
        lua_pushnil(m_State);

        while (lua_next(m_State, t) != 0) {
            printf("%s, %s", lua_typename(m_State, lua_type(m_State, -2)),
              lua_typename(m_State, lua_type(m_State, -1)));
            lua_pop(m_State, 1);
        }
    }

    bool ScriptEngine::IsScriptClass(const std::string& table) { return true; }
    std::vector<Shared<Field>>* ScriptEngine::ScriptClassGetFields(const std::string& table) { return nullptr; }

    void ScriptEngine::UpdateScriptedEntities(float delta) {}

    void ScriptEngine::UnloadScriptedEntities() {}
}
