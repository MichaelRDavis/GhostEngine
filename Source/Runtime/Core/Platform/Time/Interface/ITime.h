#pragma once

#include "Core.h"

class CORE_API ITime
{
public:
	static void StartTimer();

	static F64 GetAbsoluteTime();
};