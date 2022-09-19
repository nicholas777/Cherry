project "yaml-cpp"
    kind "StaticLib"
    language "C++"
    staticruntime "on"

    targetdir (outputDir .. outputPath .. "/%{prj.name}")
	objdir (outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

    files {
        "src/**.cpp",
        "src/**.h",
        "include/**.h"
    }

    includedirs {
        "include"
    }

    defines {
        "YAML_CPP_STATIC_DEFINE"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "Off"

        

    filter "configurations:Debug"
        runtime "Debug"
		symbols "on"

	filter "configurations:Release"
        runtime "Release"
		optimize "on"