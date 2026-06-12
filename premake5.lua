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
        project "Core"

project "Engine"
    location "Source/Runtime/Engine"
    kind "ConsoleApp"
    language "C"
    cdialect "C23"
    targetdir "Binaries"
    objdir "Intermediates"

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
    language "C"
    cdialect "C23"
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