#pragma once

#include "CoreExport.h"
#include "Core.h"

class CORE_API ITimer
{
public:
	static void StartTimer();

	static F64 GetAbsoluteTime();

private:
	static F64 m_clockFrequency;
	static U64 m_startTime;
};