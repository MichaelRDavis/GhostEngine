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
        project "RDI"
        project "OpenGLRDI"
        project "VulkanRDI"

    group "ThirdParty"
        project "glad"

project "Sandbox"
    location "Source/Sandbox/Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"

    files 
    {
        "Source/Sandbox/Sandbox/**.h",
        "Source/Sandbox/Sandbox/**.cpp"
    }

    includedirs
    {
        "Source/Sandbox/Sandbox",
        "Source/Runtime/Engine",
        "Source/Runtime/RDI",
        "Source/Runtime/Core",
        "Source/ThirdParty/SDL3-3.4.10/include"
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "Core",
        "RDI",
        "Engine",
        "SDL3",
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
        "Source/Runtime/RDI",
        "Source/Runtime/OpenGLRDI",
        "Source/Runtime/VulkanRDI",
        "Source/ThirdParty/SDL3-3.4.10/include"
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "Core",
        "RDI",
        "OpenGLRDI",
        "VulkanRDI",
        "SDL3"
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
        "Source/ThirdParty/SDL3-3.4.10/include",
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64",
    }

    links
    {
        "Core",
        "RDI",
        "SDL3",
    }

project "OpenGLRDI"
    location "Source/Runtime/OpenGLRDI"
    kind "SharedLib"
    language "C++"
    cppdialect "C++11"
    targetdir "Binaries"
    objdir "Intermediates"
    
    defines
    {
        "OPENGLRDI_EXPORT"
    }

    files 
    {
        "Source/Runtime/OpenGLRDI/**.h",
        "Source/Runtime/OpenGLRDI/**.cpp"
    }

    includedirs
    {
        "Source/Runtime/Core",
        "Source/Runtime/RDI",
        "Source/Runtime/OpenGLRDI",
        "Source/ThirdParty/SDL3-3.4.10/include",
        "Source/ThirdParty/glad/include"
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64",
    }

    links
    {
        "Core",
        "RDI",
        "SDL3",
        "glad",
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
        "Source/Runtime/RDI",
        "Source/ThirdParty/SDL3-3.4.10/include",
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64",
    }

    links
    {
        "Core",
        "SDL3",
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
        "Source/ThirdParty/SDL3-3.4.10/include"
    }

    libdirs
    {
        "Binaries",
        "Source/ThirdParty/SDL3-3.4.10/lib/x64"
    }

    links
    {
        "SDL3"
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