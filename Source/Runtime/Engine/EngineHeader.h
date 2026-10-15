#pragma once

#include "Defines.h"

#ifdef ENGINE_EXPORT
	#define ENGINE_API GHOST_DLLEXPORT
#else 
	#define ENGINE_API GHOST_DLLIMPORT
#endif