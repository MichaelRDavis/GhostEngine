#pragma once

#include "Platform/Platform.h"

class ITimer
{
public:
	static void StartTimer();

	static F64 GetAbsoluteTime();

private:
	static F64 m_clockFrequency;
	static U64 m_startTime;
};