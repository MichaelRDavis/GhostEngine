#include "System/SystemINterface/ITimer.h"

#ifdef GHOST_SYSTEM_WINDOWS
static F64 clockFrequency = 0.0f;
static LARGE_INTEGER startTime;

void ITimer::Init()
{
	LARGE_INTEGER frequency;
	QueryPerformanceCounter(&frequency);
	clockFrequency = 1.0f / (F64)frequency.QuadPart;
	QueryPerformanceCounter(&startTime);
}

F64 ITimer::GetAbsoluteTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return (F64)currentTime.QuadPart * clockFrequency;
}
#endif