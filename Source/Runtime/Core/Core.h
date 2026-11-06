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
#include "System/OS/Interface/ISystem.h"
#include "Core/Logging/Log.h"
#include "Core/Math/Math.h"
#include "Core/MemoryAllocation/Memory.h"
#include "Core/Library/Containers/Array.h"
#include "Core/Library/Containers/DynamicArray.h"
#include "Core/Library/SmartPointers/UniquePointer.h"
#include "Core/Library/SmartPointers/SharedPointer.h"
#include "Core/ObjectModel/GameObject.h"