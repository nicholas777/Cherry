#include "epch.h"
#include "scriptEngine.h"

#include <lualib.h>
#include <lauxlib.h>

namespace Cherry {
    
    void ScriptEngine::Init() {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);
    }

    void ScriptEngine::Shutdown() {
        lua_close(m_State);
    }

    Scene* ScriptEngine::GetRuntimeScene() {
    }

    void ScriptEngine::OnRuntimeStart(Scene* scene) {
    }

    void ScriptEngine::OnRuntimeStop() {
    }

    void ScriptEngine::UpdateScriptedEntities(float delta) {
    }

}
