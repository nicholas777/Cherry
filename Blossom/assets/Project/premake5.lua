project "UserProject"
	kind "SharedLib"
    language "C#"
    dotnetframework "4.8"

    targetdir ("ScriptsBin")
    objdir ("ScriptsBin/Int")

    files {
        "**.cs"
    }

    links {
        "ScriptLib"
    }

    filter "configurations:Debug"
        optimize "Off"
        symbols "Default"

    filter "configurations:Release"
        optimize "On"
        symbols "Default"

    filter "configurations:Dist"
        optimize "Full"
        symbols "Off"