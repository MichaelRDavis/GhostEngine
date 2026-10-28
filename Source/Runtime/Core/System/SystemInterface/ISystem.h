#pragma once

#include "Core.h"

struct FWindowDescription;
class IApplication;

struct FSystemInfo
{
	
};

class CORE_API ISystem
{
public:
	static FSystemInfo GetSystemInfo();

	static IApplication* CreateApplication(const FWindowDescription& winDesc);

	static void ConsoleWriteLine(const char* msg, U8 msgColor, bool isError = false);

	static void Sleep(U64 ms);
};