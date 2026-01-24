#pragma once

#include "Platform/Platform.h"

class CTimer
{
public:
	static void StartTimer();

	static F64 GetAbsoluteTime();

private:
	static F64 m_clockFrequency;
#ifdef GE_WINDOWS_PLATFORM
	static LARGE_INTEGER m_startTime;
#endif
};