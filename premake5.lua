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
        "Source/Runtime/Sandbox/**.cpp"
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
        "ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "Core",
        "Engine",
        "SDL3"
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
        "Source/Runtime/Core",
    }

    libdirs
    {
        "Binaries",
        "ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "Core",
        "SDL3"
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
        "Source/Runtime/Core/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
        "ThirdParty/SDL3-3.4.10/include"
    }

    libdirs
    {
        "Binaries",
        "ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "SDL3"
    }