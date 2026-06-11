#include "Assertions.h"

bool32 ReportAssertion(const char* expr, const char* msg, const char* file, int32 line)
{
	if (IsDebuggerPresent())
	{
		__debugbreak();
	}

	return TRUE;
}