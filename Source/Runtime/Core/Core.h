#pragma once

#include "Platform/PlatformDefines.h"
#include "Platform/PlatformDetection.h"
#include "Platform/PlatformIncludes.h"
#include "Platform/STDIncludes.h"

#ifdef CORE_EXPORT
	#define CORE_API GHOST_DLLEXPORT
#else
	#define CORE_API GHOST_DLLIMPORT
#endif

#include "Platform/AppFramework/Interface/IApplication.h"
#include "Platform/AppFramework/Interface/IWindow.h"
#include "Platform/PlatformOS/Interface/IPLatform.h"
#include "Platform/Time/Interface/ITime.h"
#include "Core/Logging/Log.h"
#include "Core/Math/Math.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector4.h"
#include "Core/MemoryAllocation/MemoryTracker.h"
#include "Core/MemoryAllocation/Memory.h"
#include "Core/Library/Containers/Array.h"
#include "Core/Library/Containers/DynamicArray.h"
#include "Core/Library/SmartPointers/UniquePointer.h"
#include "Core/Library/SmartPointers/SharedPointer.h"