#include "Timer.h"

F64 CTimer::m_clockFrequency = 0.0f;
#ifdef GE_WINDOWS_PLATFORM
LARGE_INTEGER CTimer::m_startTime;
#endif

void CTimer::StartTimer()
{
#ifdef GE_WINDOWS_PLATFORM
	LARGE_INTEGER frequency;
	QueryPerformanceCounter(&frequency);
	m_clockFrequency = 1.0f / (F64)frequency.QuadPart;
	QueryPerformanceCounter(&m_startTime);
#endif
}

F64 CTimer::GetAbsoluteTime()
{
#ifdef GE_WINDOWS_PLATFORM
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return (F64)currentTime.QuadPart * m_clockFrequency;
#endif
	return 0.0f;
}