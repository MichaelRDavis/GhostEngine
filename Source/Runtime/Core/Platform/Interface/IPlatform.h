#pragma once

#ifdef CORE_EXPORT
	#define CORE_API __declspec(dllexport)
#else
	#define CORE_API __declspec(dllimport)
#endif

class IApplication;

class CORE_API IPlatform
{
public:
	static IApplication* CreateApplication();

	static void ConsoleWriteLine(const char* msg, char msgColor = 0, bool isError = false);
};