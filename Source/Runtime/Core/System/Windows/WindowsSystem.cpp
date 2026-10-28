#include "System/SystemInterface/ISystem.h"
#include "WindowsApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
FSystemInfo ISystem::GetSystemInfo()
{
	FSystemInfo info;
	return info;
}

IApplication* ISystem::CreateApplication(const FWindowDescription& winDesc)
{
	return new CWindowsApplication(winDesc);
}

void ISystem::ConsoleWriteLine(const char* msg, U8 msgColor, bool isError)
{
	HANDLE consoleHandle = nullptr;
	static U8 colors[6] = { 64, 4, 6, 2, 1, 8 };

	if (isError)
	{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else
	{
		consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
	}

	if (consoleHandle != nullptr)
	{
		SetConsoleTextAttribute(consoleHandle, colors[msgColor]);

		U64 length = strlen(msg);
		LPDWORD numWritten = 0;
		WriteConsoleA(consoleHandle, msg, (DWORD)length, numWritten, 0);
	}
}

void ISystem::Sleep(U64 ms)
{
	::Sleep(ms);
}
#endif