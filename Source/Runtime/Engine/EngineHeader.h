#pragma once

#include "Platform/PlatformDefines.h"
#include "Platform/PlatformDetection.h"
#include "Platform/PlatformIncludes.h"

#ifdef ENGINE_EXPORT
	#define ENGINE_API GHOST_DLLEXPORT
#else 
	#define ENGINE_API GHOST_DLLIMPORT
#endif