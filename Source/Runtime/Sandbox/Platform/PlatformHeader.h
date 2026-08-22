#pragma once

#include "EngineTypes.h"
#include "STDHeaders.h"

#ifdef GE_WINDOWS_PLATFORM
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <SDL3/SDL.h>
#endif

#define GE_OPENGL_RENDERER
//#define GE_VULKAN_RENDERER