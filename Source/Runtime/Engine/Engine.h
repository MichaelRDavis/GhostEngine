#pragma once

#include "Core.h"

#ifdef ENGINE_EXPORT
	#define ENGINE_API GHOST_DLLEXPORT
#else
	#define ENGINE_API GHOST_DLLIMPORT
#endif

#include "Engine/EngineLoop/EngineLoop.h"