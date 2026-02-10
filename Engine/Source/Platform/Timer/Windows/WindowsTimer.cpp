#include "Platform/Timer/ITimer.h"

F64 ITimer::m_clockFrequency = 0.0f;
U64 ITimer::m_startTime;

#ifdef GE_WINDOWS_PLATFORM
static LARGE_INTEGER startTime;

void ITimer::StartTimer()
{
	LARGE_INTEGER frequency;
	QueryPerformanceCounter(&frequency);
	m_clockFrequency = 1.0f / (F64)frequency.QuadPart;
	QueryPerformanceCounter(&startTime);
	m_startTime = startTime.QuadPart;
}

F64 ITimer::GetAbsoluteTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return (F64)currentTime.QuadPart * m_clockFrequency;
	return 0.0f;
}
#endif