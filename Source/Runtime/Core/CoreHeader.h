#pragma once

#include "Platform/PlatformDefines.h"
#include "Platform/PlatformDetection.h"
#include "Platform/PlatformIncludes.h"

#include <cstdlib>

#ifdef CORE_EXPORT
	#define CORE_API GHOST_DLLEXPORT
#else 
	#define CORE_API GHOST_DLLIMPORT
#endif