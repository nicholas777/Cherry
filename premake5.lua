outputDir = "bin/"
outputPath = "%{cfg.platform}.%{cfg.buildcfg}.%{cfg.architecture}"

projectDir = "Blossom/assets/Project"

workspace "Cherry"
	architecture "x64"
	startproject "Blossom"

	configurations {
		"debug",
		"release",
		"dist"
	}

    -- Projects
    include "Cherry"
    include "Blossom"
    include "ScriptLib"

	-- Game
	include (projectDir)

    -- Dependencies
	group "Dependencies"
		include "Cherry/vendor/GLFW"
		include "Cherry/vendor/GLAD"
		include "Cherry/vendor/Freetype"
		include "Cherry/vendor/FreetypeGL"
		include "Cherry/vendor/imgui"
		include "Cherry/vendor/yaml-cpp"