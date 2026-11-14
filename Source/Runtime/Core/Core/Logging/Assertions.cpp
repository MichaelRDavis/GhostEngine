#include "Assertions.h"

bool AssertFailed(const char* file, I32 line, const char* expression)
{
	GHOST_LOG(Error, "Assertion Failed: %s(%d): '%s'", file, line, expression);

#ifdef GHOST_PLATFORM_WINDOWS
	if (IsDebuggerPresent())
	{
		__debugbreak();
	}
#endif

	return true;
}