#include "Platform/Interface/IPlatform.h"

#ifdef _WIN64
#include <cstdio>

void IPlatform::ConsoleWriteLine(const char* msg)
{
	printf("%s\n", msg);
}
#endif