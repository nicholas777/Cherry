
function CreateScript(name)
    __CHERRY_SCRIPTS__[name] = { __IS_SCRIPT=true }
    return __CHERRY_SCRIPTS__[name]
end

CreateScript("player");
CreateScript("object");
CreateScript("enemy");
CreateScript("skybox");
CreateScript("ai");
CreateScript("inventory");

