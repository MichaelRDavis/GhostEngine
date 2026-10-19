#pragma once

#include "Platform/PlatformDefines.h"
#include "Platform/PlatformDetection.h"
#include "Platform/PlatformIncludes.h"

#ifdef VULKANRDI_EXPORT
	#define VULKANRDI_API GHOST_DLLEXPORT
#else 
	#define VULKANRDI_API GHOST_DLLIMPORT
#endif