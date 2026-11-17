workspace "GhostEngine"
    configurations 
    {
        "DebugGame",
        "ReleaseGame",
        "DebugEditor",
        "ReleaseEditor"
    }

    platforms
    { 
        "x64"
    }

    startproject "Sandbox"

    filter { "configurations:DebugGame" }
        symbols "On"
        defines "GHOST_DEBUG_GAME"
    filter { "configurations:ReleaseGame" }
        optimize "On"
        defines "GHOST_RELEAE_GAME"
    filter { "configurations:DebugEditor" }
        symbols "On"
        defines "GHOST_DEBUG_EDITOR"
    filter { "configurations:ReleaseEditor" }
        optimize "On"
         defines "GHOST_RELEASE_EDITOR"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

    group "Engine"
        project "Core"
        project "RDI"
        project "VulkanRDI"
        project "Engine"
    group "Editor"
        project "Sandbox"

project "Sandbox"
    location "Source/Runtime/Sandbox"
    kind "WindowedApp"
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
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/RDI",
        "Source/Runtime/Core",

        "C:/VulkanSDK/1.4.357.0/Include"
    }

    libdirs
    {
        "Binaries"
    }

    links
    {
        "Core",
        "Engine",
        "RDI",
        "VulkanRDI"
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
        "Source/Runtime/RDI",
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/Engine",

        "C:/VulkanSDK/1.4.357.0/Include"
    }

    libdirs
    {
        "Binaries"
    }

    links
    {
        "Core",
        "RDI",
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
        "Source/Runtime/RDI",
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
        "RDI",

        "volk"
    }

project "RDI"
    location "Source/Runtime/RDI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    defines
    {
        "RDI_EXPORT"
    }

    files 
    {
        "Source/Runtime/RDI/**.h",
        "Source/Runtime/RDI/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
        "Source/Runtime/RDI"
    }

    libdirs
    {
        "Binaries"
    }

    links
    {
        "Core"
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
        "Source/Runtime/Core"
    }

    libdirs
    {
        "Binaries"
    }