outputDir = "bin/"
outputPath = "%{cfg.platform}.%{cfg.buildcfg}.%{cfg.architecture}"

appName = "Tests"

workspace "Engine"
	architecture "x64"

	configurations {
		"debug",
		"release",
		"dist"
	}

include "Cherry/vendor/GLFW"
include "Cherry/vendor/GLAD"

-- NOT TO BE MODIFIED
project "Cherry"
	location "Cherry"
	kind "SharedLib"
	language "C++"
	
	targetdir (outputDir .. outputPath .. "/%{prj.name}")
	objdir (outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	pchheader "epch.h"
	pchsource "Cherry/src/epch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLAD/include",
		"%{prj.name}/vendor/stb_image"
	}

	links {
		"GLFW",
		"GLAD",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"CH_PLATFORM_WINDOWS",
			"CH_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands {
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputPath .. "/" .. appName)
		}

	filter "configurations:debug"
		defines "CH_DEBUG_MODE"
		symbols "On"

	filter "configurations:release"
		defines "CH_RELEASE_MODE"
		optimize "On"

	filter "configurations:dist"
		defines "CH_DIST_MODE"
		optimize "On" 

project "Tests"
	location "tests"
	kind "ConsoleApp"
	language "C++"
	
	targetdir (outputDir .. outputPath .. "/%{prj.name}")
	objdir (outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Cherry/src",
		"Cherry/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"CH_PLATFORM_WINDOWS",
		}

		links {
			"Cherry"
		}

	filter "configurations:debug"
		defines "CH_DEBUG_MODE"
		symbols "On"

	filter "configurations:release"
		defines "CH_RELEASE_MODE"
		optimize "On"

	filter "configurations:dist"
		defines "CH_DIST_MODE"
		optimize "On" 
