#include "Log.h"

static char* verbosityStrings[6] =
{
	"[FATAL]: ",
	"[ERROR]: ",
	"[WARNING]: ",
	"[INFO]: ",
	"[LOG]: ",
	"[VERBOSE]: "
	"[VERYVERBOSE]: "
};

std::vector<SLogEntry> CLog::mLogEntries;

void CLog::Init()
{

}

void CLog::Destroy()
{
	Clear();
}

void CLog::Clear()
{
	mLogEntries.clear();
}

void CLog::LogMessage(ELogVerbosity verbosity, const char* msg, ...)
{
	char message[32000];
	CMemory::Set(message, 0, sizeof(message));

	va_list argPtr;
	va_start(argPtr, msg);
	vsnprintf(message, 32000, msg, argPtr);
	va_end(argPtr);

	time_t currentTime = time(nullptr);
	tm* localTime = localtime(&currentTime);

	SLogEntry logEntry;
	logEntry.category = "[DEBUG]: ";
	logEntry.msg = message;
	logEntry.verbosity = verbosity;
	logEntry.localTime = currentTime;
	mLogEntries.push_back(logEntry);

	char outputMessage[32000];
	sprintf(outputMessage, "%s%s\n", verbosityStrings[verbosity], message);

	switch (verbosity)
	{
	case ELogVerbosity::Fatal:
		LogMessageToConsole(ELogVerbosity::Fatal, outputMessage, true);
		ISystem::DisplayMessageBox(outputMessage, "Fatal");
		break;
	case ELogVerbosity::Error:
		LogMessageToConsole(ELogVerbosity::Error, outputMessage, true);
		ISystem::DisplayMessageBox(outputMessage, "Error");
		break;
	case ELogVerbosity::Warning:
		LogMessageToConsole(ELogVerbosity::Warning, outputMessage, true);
		ISystem::DisplayMessageBox(outputMessage, "Warning");
		break;
	case ELogVerbosity::Info:
		LogMessageToConsole(ELogVerbosity::Info, outputMessage);
		LogMessageToIDE(outputMessage);
		break;
	case ELogVerbosity::Log:
		LogMessageToConsole(ELogVerbosity::Log, outputMessage);
		LogMessageToIDE(outputMessage);
		break;
	case ELogVerbosity::Verbose:
		LogMessageToIDE(outputMessage);
		break;
	case ELogVerbosity::VeryVerbose:
		LogMessageToIDE(outputMessage);
		break;
	default:
		break;
	}
}

void CLog::LogMessageToConsole(ELogVerbosity verbosity, const char* msg, bool isError)
{
#ifdef GHOST_SYSTEM_WINDOWS
	U64 length = strlen(msg);
	LPDWORD numWritten = 0;

	static U8 verbosityColors[6] =
	{
		64, 4, 6, 2, 1, 8
	};

	if (isError)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), verbosityColors[verbosity]);
		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), msg, (DWORD)length, numWritten, 0);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), verbosityColors[verbosity]);
		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, (DWORD)length, numWritten, 0);
	}
#endif
}

void CLog::LogMessageToIDE(const char* msg)
{
#ifdef GHOST_MSVC_COMPILER
	OutputDebugStringA(msg);
#endif
}