#include "IPlatform.h"
#include "ApplicationCore/IApplication.h"
#include <cstdio>

IApplication* IPlatform::CreateApplication(const ApplicationInfo& appInfo)
{
	return new IApplication(appInfo);
}

void IPlatform::WriteToConsole(const char* msg)
{
	printf("%s\n", msg);
}