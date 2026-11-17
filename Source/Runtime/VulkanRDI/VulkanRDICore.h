#pragma once

#include "Core.h"
#include "RDICore.h"

#ifdef VULKANRDI_EXPORT
#define VULKANRDI_API GHOST_DLLEXPORT
#else
#define VULKANRDI_API GHOST_DLLIMPORT
#endif

#include "VulkanCore/VulkanIncludes.h"
#include "VulkanRenderer/VulkanRDI.h"