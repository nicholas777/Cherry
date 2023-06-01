project "ScriptLib"
    kind "SharedLib"
    language "C#"
    dotnetframework "4.8"

    targetdir ("../Blossom/assets/CoreScripts")
    objdir ("../Blossom/assets/CoreScripts/Intermediate")

    files {
        "src/**.cs"
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