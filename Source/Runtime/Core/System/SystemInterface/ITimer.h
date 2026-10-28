#pragma once

#include "Core.h"

class CORE_API ITimer
{
public:
	static void Init();

	static F64 GetAbsoluteTime();
};