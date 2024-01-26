#include "scriptEngine.h"

#include "core/core.h"
#include "epch.h"
#include "lua.h"

#include <lauxlib.h>
#include <lualib.h>

namespace Cherry {

    void ScriptEngine::Init() {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);

        // Expose some useful variables
        lua_pushstring(m_State, CH_VERSION);
        lua_setglobal(m_State, "CH_VERSION");
    }

    void ScriptEngine::Shutdown() {
        lua_close(m_State);
    }

    Scene* ScriptEngine::GetRuntimeScene() {}

    void ScriptEngine::OnRuntimeStart(Scene* scene) {}

    void ScriptEngine::OnRuntimeStop() {}

    void ScriptEngine::UpdateScriptedEntities(float delta) {}

}
