
function CreateScript(name)
    __CHERRY_SCRIPTS__[name] = { __IS_SCRIPT=true }
    return __CHERRY_SCRIPTS__[name]
end

print(CreateScript("player"))
print(CreateScript("object"))
print(CreateScript("enemy"))
print(CreateScript("skybox"))
print(CreateScript("ai"))
print(CreateScript("inventory"))

