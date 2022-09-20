outputDir = "bin/"
outputPath = "%{cfg.platform}.%{cfg.buildcfg}.%{cfg.architecture}"

workspace "Cherry"
	architecture "x64"
	startproject "Blossom"

	configurations {
		"debug",
		"release",
		"dist"
	}

	include "Cherry/vendor/GLFW"
	include "Cherry/vendor/GLAD"
	include "Cherry/vendor/Freetype"
	include "Cherry/vendor/FreetypeGL"
	include "Cherry/vendor/imgui"
    include "Cherry/vendor/yaml-cpp"

project "Cherry"
	location "Cherry"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	
	targetdir (outputDir .. outputPath .. "/%{prj.name}")
	objdir (outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	pchheader "epch.h"
	pchsource "Cherry/src/epch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/EnTT/entt.hpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/GLFW/include",
		"%{prj.name}/vendor/GLAD/include",
		"%{prj.name}/vendor/Freetype/include",
		"%{prj.name}/vendor/FreetypeGL",
		"%{prj.name}/vendor/stb_image",
		"%{prj.name}/vendor/EnTT",
		"%{prj.name}/vendor/imgui",
		"%{prj.name}/vendor/yaml-cpp/include"
	}

	links {
		"GLFW",
		"GLAD",
		"Freetype",
		"FreetypeGL",
		"ImGui",
		"yaml-cpp",
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
			("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputPath .. "/Blossom")
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

project "Blossom"
	location "Blossom"
	kind "ConsoleApp"
	language "C++"
	staticruntime "On"

	targetdir (outputDir .. outputPath .. "/%{prj.name}")
	objdir (outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Cherry/src",
		"Cherry/vendor/spdlog/include",
		"Cherry/vendor/FreetypeGL",
		"Cherry/vendor/GLAD/include",
		"Cherry/vendor/EnTT",
		"Cherry/vendor/imgui",
		"Cherry/vendor/yaml-cpp/include",
		"Blossom/src"
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
