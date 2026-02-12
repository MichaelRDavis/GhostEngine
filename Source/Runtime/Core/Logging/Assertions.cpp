#include "Assertions.h"
#include "Log.h"

void AssertFailed(const char* file, I32 line, const char* expr)
{
	GE_LOG(Fatal, "Assertion: %s(%d): '%s'", file, line, expr);

#ifdef GE_MSVC_COMPILER
	if (IsDebuggerPresent())
	{
		__debugbreak();
	}
#endif
}