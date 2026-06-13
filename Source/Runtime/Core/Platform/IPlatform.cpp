#include "IPlatform.h"
#include <cstdio>

void IPlatform::WriteToConsole(const char* msg)
{
	printf("%s\n", msg);
}