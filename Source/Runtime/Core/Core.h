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

#include "System/SystemInterface/ISystem.h"
#include "System/SystemInterface/IApplication.h"
#include "System/SystemInterface/ITimer.h"
#include "Core/Logging/Log.h"
#include "Core/Memory/Memory.h"
#include "Core/Library/SmartPointers/UniquePointer.h"
#include "Core/Library/Containers/Array.h"
#include "Core/Library/Containers/DynamicArray.h"