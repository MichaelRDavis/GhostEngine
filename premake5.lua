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
        project "Core"
        project "VulkanRDI"
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
        "Source/Runtime/Core",
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/Engine",
        "Source/Runtime/Sandbox"
    }

    libdirs
    {
        "Binaries",
    }

    links
    {
        "Core",
        "VulkanRDI",
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
        "Source/Runtime/Engine/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/Engine"
    }

    libdirs
    {
        "Binaries",
    }

    links
    {
        "Core",
        "VulkanRDI"
    }

project "VulkanRDI"
    location "Source/Runtime/VulkanRDI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    defines
    {
        "VULKANRDI_EXPORT"
    }

    files 
    {
        "Source/Runtime/VulkanRDI/**.h",
        "Source/Runtime/VulkanRDI/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
        "Source/Runtime/VulkanRDI",

        "C:/VulkanSDK/1.4.357.0/Include"
    }

    libdirs
    {
        "Binaries",

        "C:/VulkanSDK/1.4.357.0/Lib"
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
        "Source/Runtime/Core/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
    }

    libdirs
    {
        "Binaries",
    }