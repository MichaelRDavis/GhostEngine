#pragma once

#include "System/SystemDefines.h"
#include "System/SystemDetection.h"
#include "System/SystemIncludes.h"
#include "System/STDIncludes.h"

#ifdef CORE_EXPORT
	#define CORE_API GHOST_DLLEXPORT
#else
	#define CORE_API GHOST_DLLIMPORT
#endif

#include "System/AppFramework/Interface/IApplication.h"
#include "System/AppFramework/Interface/IWindow.h"
#include "System/SystemOS/Interface/ISystem.h"

#include "Core/Logging/Log.h"