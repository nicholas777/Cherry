project "Cherry"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	
	targetdir ("../" .. outputDir .. outputPath .. "/%{prj.name}")
	objdir ("../" .. outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	pchheader "epch.h"
	pchsource "src/epch.cpp"

	files {
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/EnTT/entt.hpp"
	}

	includedirs {
		"src",
		"vendor/spdlog/include",
		"vendor/GLFW/include",
		"vendor/GLAD/include",
		"vendor/Freetype/include",
		"vendor/FreetypeGL",
		"vendor/stb_image",
		"vendor/EnTT",
		"vendor/imgui",
		"vendor/yaml-cpp/include",
		"vendor/mono/include"
	}

	links {
		"GLFW",
		"GLAD",
		"Freetype",
		"FreetypeGL",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib",
		"vendor/mono/lib/%{cfg.buildcfg}/libmono-static-sgen.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "Off"
		systemversion "latest"

		defines {
			"CH_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			-- "CH_BUILD_DLL"
		}

        links {
            "Ws2_32.lib",
            "Winmm.lib",
            "Version.lib",
            "Bcrypt.lib",
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