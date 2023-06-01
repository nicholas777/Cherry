project "Blossom"
	kind "ConsoleApp"
	language "C++"
	staticruntime "On"

	targetdir ("../" .. outputDir .. outputPath .. "/%{prj.name}")
	objdir ("../" .. outputDir .. "/int/" .. outputPath .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.cpp"
	}

	includedirs {
		"../Cherry/src",
		"../Cherry/vendor/spdlog/include",
		"../Cherry/vendor/FreetypeGL",
		"../Cherry/vendor/GLAD/include",
		"../Cherry/vendor/EnTT",
		"../Cherry/vendor/imgui",
		"../Cherry/vendor/yaml-cpp/include",
        "../Cherry/vendor/mono/include",
		"src"
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
