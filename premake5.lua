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

    startproject "Sandbox"

    filter { "configurations:Debug" }
        symbols "On"
    filter { "configurations:Release" }
        optimize "On"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

    group "Engine"
        project "Engine"
    group "Editor"
        project "Sandbox"

project "Sandbox"
    location "Source/Runtime/Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    files 
    {
        "Source/Runtime/Sandbox/**.h",
        "Source/Runtime/Sandbox/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Sandbox",
        "Source/Runtime/Engine",

        "Source/ThirdParty/SDL3-3.4.10/include",
    }

    libdirs
    {
        "Binaries",
    }

    links
    {
        "Engine",
    }

project "Engine"
    location "Source/Runtime/Engine"
    kind "SharedLib"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    defines
    {
        "ENGINE_EXPORT"
    }

    files 
    {
        "Source/Runtime/Engine/**.h",
        "Source/Runtime/Engine/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Engine",

        "Source/ThirdParty/SDL3-3.4.10/include",
    }

    libdirs
    {
        "Binaries",

        "Source/ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "SDL3",
    }