#include "Platform/Time/Interface/ITime.h"

#ifdef GHOST_PLATFORM_WINDOWS
static F64 clockFrequnecy = 0.0f;
static LARGE_INTEGER startTime;

void ITime::StartTimer()
{
	LARGE_INTEGER frequency;
	QueryPerformanceCounter(&frequency);
	clockFrequnecy = 1.0f / (F64)frequency.QuadPart;
	QueryPerformanceCounter(&startTime);
}

F64 ITime::GetAbsoluteTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return (F64)currentTime.QuadPart * clockFrequnecy;
}
#endif