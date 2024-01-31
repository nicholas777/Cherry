
struct lua_State;

namespace Cherry {

    enum LuaStatusCode {
        Success = 0,
        InvalidParameters = 1,
    };

    void registerScriptingApi(lua_State* state);

}
