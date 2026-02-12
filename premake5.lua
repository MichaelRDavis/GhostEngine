workspace "GhostEngine"
    configurations 
    {
        "DebugGame",
        "ReleaseGame",
    }

    platforms
    {
        "x64"
    }

    filter { "configurations:DebugGame" }
        symbols "On"
    filter { "configurations:ReleaseGame" }
        optimize "On"

    filter { "platforms:x64" }
        system "Windows"
        architecture "x86_64"

    group "Engine"
        project "GhostGame"
        project "Engine"
        project "VulkanRDI"
        project "RDI"
        project "Core"

project "GhostGame"
    location "Source/Runtime/GhostGame"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries"
    objdir "Intermediates"

    files 
    {
        "Source/Runtime/GhostGame/**.h",
        "Source/Runtime/GhostGame/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/GhostGame",
        "Source/Runtime/Engine",
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/RDI",
        "Source/Runtime/Core"
    }

    libdirs
    {
        "Binaries"
    }

    links
    {
        "Core",
        "RDI",
        "VulkanRDI",
        "Engine"
    }

project "Engine"
    location "Source/Runtime/Engine"
    kind "Sharedlib"
    language "C++"
    cppdialect "C++20"
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
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/RDI",
        "Source/Runtime/Core",

        "C:/VulkanSDK/1.4.304.1/Include"
    }

    libdirs
    {
        "Binaries"
    }

    links
    {
        "Core",
        "RDI",
        "VulkanRDI",
    }

project "VulkanRDI"
    location "Source/Runtime/VulkanRDI"
    kind "Sharedlib"
    language "C++"
    cppdialect "C++20"
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
        "Source/Runtime/VulkanRDI",
        "Source/Runtime/RDI",
        "Source/Runtime/Core",

        "C:/VulkanSDK/1.4.304.1/Include"
    }

    libdirs
    {
        "Binaries",

        "C:/VulkanSDK/1.4.304.1/Lib"
    }

    links
    {
        "Core",
        "RDI",

        "volkd.lib"
    }

project "RDI"
    location "Source/Runtime/RDI"
    kind "Sharedlib"
    language "C++"
    cppdialect "C++20"
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
        "Source/Runtime/RDI",
        "Source/Runtime/Core"
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
    kind "Sharedlib"
    language "C++"
    cppdialect "C++20"
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