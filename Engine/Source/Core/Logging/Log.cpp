#include "Log.h"
#include "Platform/Platform.h"

void CLog::Init()
{

}

void CLog::Destroy()
{

}

void CLog::LogMessage(ELogVerbosity verbosity, const char* msg, ...)
{
	const char* verbosityStrings[7] =
	{
		"Fatal: ",
		"Error: ",
		"Warning: ",
		"Display: ",
		"Log: ",
		"Verbose: ",
		"VeryVerbose: "
	};

	char msgBuffer[32000];
	memset(msgBuffer, 0, sizeof(msgBuffer));

#ifdef GE_MSVC_COMPILER
	va_list argPtr;
#endif
	va_start(argPtr, msg);
	vsnprintf(msgBuffer, 32000, msg, argPtr);
	va_end(argPtr);

	char outputBuffer[32000];
	sprintf(outputBuffer, "%s%s\n", verbosityStrings[verbosity], msgBuffer);

	switch (verbosity)
	{
	case Fatal:
		LogToConsole(outputBuffer);
		LogCrash(outputBuffer);
		break;
	case Error:
		LogToConsole(outputBuffer);
		break;
	case Warning:
		LogToConsole(outputBuffer);
		break;
	case Display:
		LogToConsole(outputBuffer);
		break;
	case Log:
		LogToConsole(outputBuffer);
		break;
	case Verbose:
		LogToConsole(outputBuffer);
		break;
	case VeryVerbose:
		LogToConsole(outputBuffer);
		break;
	}
}

void CLog::LogToIDE(const char* msg)
{
#ifdef GE_MSVC_COMPILER
	OutputDebugStringA(msg);
#endif
}

void CLog::LogToConsole(const char* msg, bool isError)
{
#ifdef GE_WINDOWS_PLATFORM
	HANDLE outputHandle = nullptr;
	if (isError)
	{
		outputHandle = GetStdHandle(STD_ERROR_HANDLE);
	}
	else
	{
		outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	DWORD bytesWritten = 0;
	WriteConsoleA(outputHandle, msg, (DWORD)strlen(msg), &bytesWritten, nullptr);
#endif
}

void CLog::LogCrash(const char* msg)
{
#ifdef GE_WINDOWS_PLATFORM
	MessageBoxA(nullptr, msg, "Error", MB_ICONERROR | MB_OKCANCEL);
	ExitProcess(0);
#endif
}