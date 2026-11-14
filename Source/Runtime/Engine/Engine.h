#pragma once

#include "Core.h"

#ifdef ENGINE_EXPORT
	#define ENGINE_API GHOST_DLLEXPORT
#else
	#define ENGINE_API GHOST_DLLIMPORT
#endif

#include "Engine/EngineLoop/EngineLoop.h"
#include "Engine/EngineFramework/IEngine.h"
#include "Engine/EngineFramework/GameEngine.h"
#include "Engine/EngineFramework/SandboxEngine.h"