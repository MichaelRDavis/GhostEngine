#include "Log.h"
#include "Core.h"
#include "Platform/OS/IPlatform.h"
#include "FileSystem/IFileStream.h"

std::unique_ptr<IFileStream> CLog::m_logFile;
std::vector<LogEntry> CLog::m_logEntries;

static const char* verbosityStrings[7] =
{
	"Fatal: ",
	"Error: ",
	"Warning: ",
	"Display: ",
	"Log: ",
	"Verbose: ",
	"VeryVerbose: "
};

void CLog::Init()
{
	m_logFile = std::make_unique<IFileStream>();
	m_logFile->Open("Log.txt", Write, Overwrite);
}

void CLog::Destroy()
{
	m_logEntries.clear();
}

void CLog::LogMessage(ELogVerbosity verbosity, const char* msg, ...)
{
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

	LogEntry log;
	log.category = 0;
	log.verbosity = verbosity;
	log.msg = outputBuffer;

	m_logEntries.emplace_back(log);

	switch (verbosity)
	{
	case Fatal:
		LogToConsole(outputBuffer, verbosity);
		LogToFile(outputBuffer);
		LogCrash(outputBuffer);
		break;
	case Error:
		LogToFile(outputBuffer);
		LogToConsole(outputBuffer, verbosity);
		break;
	case Warning:
		LogToFile(outputBuffer);
		LogToConsole(outputBuffer, verbosity);
		break;
	case Display:
		LogToFile(outputBuffer);
		LogToConsole(outputBuffer, verbosity);
		break;
	case Log:
		LogToFile(outputBuffer);
		break;
	case Verbose:
		LogToFile(outputBuffer);
		break;
	case VeryVerbose:
		LogToFile(outputBuffer);
		break;
	}
}

void CLog::LogToIDE(const char* msg)
{
#ifdef GE_MSVC_COMPILER
	OutputDebugStringA(msg);
#endif
}

void CLog::LogToConsole(const char* msg, U8 color, bool isError)
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

	static U8 verbosityColors[7] = { 4, 4, 6, 8, 8, 8, 8, };
	SetConsoleTextAttribute(outputHandle, verbosityColors[color]);

	DWORD bytesWritten = 0;
	WriteConsoleA(outputHandle, msg, (DWORD)strlen(msg), &bytesWritten, nullptr);
#endif
}

void CLog::LogToFile(const char* msg)
{
	m_logFile->Write(msg);
}

void CLog::LogCrash(const char* msg)
{
#ifdef GE_WINDOWS_PLATFORM
	MessageBoxA(nullptr, msg, "Error", MB_ICONERROR | MB_OKCANCEL);
#endif

	IPlatform::Exit();
}