#pragma once

#include "Platform/Platform.h"

#define VK_NO_PROTOTYPES
#include <volk/volk.h>
#ifdef _WIN64
#include <vulkan/vulkan_win32.h>
#endif