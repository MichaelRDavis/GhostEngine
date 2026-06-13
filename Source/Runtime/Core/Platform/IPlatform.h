#pragma once

#include "CoreExport.h"

struct ApplicationInfo;
class IApplication;

class CORE_API IPlatform
{
public:
	static IApplication* CreateApplication(const ApplicationInfo& appInfo);

	static void WriteToConsole(const char* msg);
};