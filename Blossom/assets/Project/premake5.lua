
EngineRoot = "../../.."

include (EngineRoot .. "/premake-customization.lua")

workspace "Project"

	architecture "x64"

	configurations {
		"debug",
		"release",
		"dist"
	}

project "UserProject"
	kind "SharedLib"
    language "C#"
    dotnetframework "4.8"

    targetdir ("ScriptsBin")
    objdir ("ScriptsBin/Int")

    files {
        "Assets/**.cs"
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

group "Cherry"
    include (EngineRoot .. "/ScriptLib")
group ""
