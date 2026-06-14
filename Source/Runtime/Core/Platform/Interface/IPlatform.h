#pragma once

#ifdef CORE_EXPORT
	#define CORE_API __declspec(dllexport)
#else
	#define CORE_API __declspec(dllimport)
#endif

class CORE_API IPlatform
{
public:
	static void ConsoleWriteLine(const char* msg);
};