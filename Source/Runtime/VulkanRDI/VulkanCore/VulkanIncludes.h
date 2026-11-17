#pragma once

#ifdef GHOST_PLATFORM_WINDOWS
	#define VK_USE_PLATFORM_WIN32_KHR
#endif
#define VK_NO_PROTOTYPES
#include <vma/vk_mem_alloc.h>
#include <volk/volk.h>
#ifdef GHOST_PLATFORM_WINDOWS
	#include <vulkan/vulkan_win32.h>
#endif