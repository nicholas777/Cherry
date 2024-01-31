#include "entt/entity/fwd.hpp"
#include "epch.h"
#include "api.h"

#include "scriptEngine.h"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace Cherry {

    static int getComponent([[maybe_unused]] lua_State* L) {
        //uint32_t entity = (uint32_t)luaL_checkinteger(L, 1);
        //uint32_t type = (uint32_t)luaL_checkinteger(L, 2);

        //Entity e = Entity((entt::entity)entity, ScriptEngine::GetRuntimeScene());

        //switch (type) {}

        return 1;
    }

    void registerScriptingApi(lua_State* L) {
        lua_createtable(L, 0, 10);
        lua_setglobal(L, "__CPP_API");

        lua_getglobal(L, "__CPP_API");

        lua_pushcfunction(L, &getComponent);
        lua_setfield(L, -2, "getComponent");
    }

}

