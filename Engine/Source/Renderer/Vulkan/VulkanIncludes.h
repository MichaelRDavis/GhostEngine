#pragma once

#include "Platform/Platform.h"

#ifdef _WIN64
#define VK_USE_PLATFORM_WIN32_KHR
#endif
#define VK_NO_PROTOTYPES
#include <volk/volk.h>
#ifdef _WIN64
#include <vulkan/vulkan_win32.h>
#endif