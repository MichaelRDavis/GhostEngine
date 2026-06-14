#include "Platform/Interface/IPlatform.h"

#ifdef _WIN64
#include "ApplicationCore/Windows/WindowsApplication.h"

IApplication* IPlatform::CreateApplication()
{
	return new CWindowsApplication();
}

void IPlatform::ConsoleWriteLine(const char* msg, char msgColor, bool isError)
{
	HANDLE consoleHandle;
	if (isError)
	{
		consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
	}
	else
	{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	static char colors[6] = {64, 4, 6, 2, 1, 8};
	SetConsoleTextAttribute(consoleHandle, colors[msgColor]);
}
#endif