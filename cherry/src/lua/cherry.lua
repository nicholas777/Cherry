
function CreateScript(name)
    __CHERRY_SCRIPTS__[name] = { __IS_SCRIPT=true }
    __CHERRY_SCRIPTS__[name].__new_obj = function (obj)
        obj = {}
        -- Move this to C land
        setmetatable(obj, __CHERRY_SCRIPTS__[name])
        __CHERRY_SCRIPTS__[name].__index = __CHERRY_SCRIPTS__[name]
        return obj
    end
    return __CHERRY_SCRIPTS__[name]
end

local x1 = CreateScript("player")
x1.onCreate = function ()
    print("Player created")
end

x1.onUpdate = function (delta)
    print(delta)
end

x1.variable = "Text"

local x2 = CreateScript("object")
x2.onCreate = function ()
    print("Object created")
end

x2.onUpdate = function (delta)
    print(delta)
end

x2.num = 31
x2.hello = "Hello"

local x3 = CreateScript("enemy")
x3.onCreate = function ()
    print("Enemy created");
end

x3.onUpdate = function (delta)
    print(delta)
end

