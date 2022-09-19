project "FreetypeGL"
	kind "StaticLib"
    language "C"
    staticruntime "On"

    includedirs
    {
        "../Freetype/include"
    }

    files
    {
        "texture-font.c",
        "texture-atlas.c",
        "vector.c",
        "ftgl-utils.c",
        "utf8-utils.c",
        "distance-field.c",
        "edtaa3func.c"
    }

    filter "configurations:Debug"
        runtime "Debug"
		symbols "on"
      
    filter "configurations:Release"

        runtime "Release"
		optimize "on"