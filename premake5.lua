workspace "GhostEngine"
    configurations 
    {
        "Debug",
        "Release",
    }

    platforms
    {   -- VS 2026 does not support custom platform names
        "x64"
    }

    startproject "Engine"

    filter { "configurations:Debug" }
        symbols "On"
    filter { "configurations:Release" }
        optimize "On"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

    group "Engine"
        project "Engine"

    group "ThirdParty"
        project "glad"

project "Engine"
    location "Source/Runtime/Engine"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    files 
    {
        "Source/Runtime/Engine/**.h",
        "Source/Runtime/Engine/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Engine",
        "Source/ThirdParty/SDL3-3.4.10/include",
        "Source/ThirdParty/glad/include"
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "SDL3",
        "glad"
    }

project "glad"
    location "Source/ThirdParty/glad"
    kind "StaticLib"
    language "C"
    targetdir "Binaries"
    objdir "Intermediates"

    files 
    {
        "Source/ThirdParty/glad/include/**.h",
        "Source/ThirdParty/glad/src/**.c"
    }

    includedirs
    {
       "Source/ThirdParty/glad/include"
    }