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

    group "Sandbox"
        project "Sandbox"

    group "Engine"
        project "Engine"
        project "Core"

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
        "Source/Runtime/Sandbox/**.c"
    }

    includedirs
    {
        "Source/Runtime/Sandbox",
        "Source/Runtime/Engine",
        "Source/Runtime/Core",
    }

    libdirs
    {
        "Binaries",
    }

    links
    {
        "Core",
        "Engine"
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
        "Source/Runtime/Engine/**.c"
    }

    includedirs
    {
        "Source/Runtime/Engine",
        "Source/Runtime/Core",
    }

    libdirs
    {
        "Binaries",
    }

    links
    {
        "Core",
    }

project "Core"
    location "Source/Runtime/Core"
    kind "SharedLib"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"
    
    defines
    {
        "CORE_EXPORT"
    }

    files 
    {
        "Source/Runtime/Core/**.h",
        "Source/Runtime/Core/**.c"
    }

    includedirs
    {
        "Source/Runtime/Core",
    }

    libdirs
    {
        "Binaries",
    }

    links
    {

    }