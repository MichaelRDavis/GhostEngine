#pragma once

#include "CoreExport.h"
#include "Core.h"

class IFileStream;

enum ELogVerbosity
{
	Fatal,
	Error,
	Warning,
	Display,
	Log,
	Verbose,
	VeryVerbose
};

struct LogEntry
{
	U32 category;
	ELogVerbosity verbosity;
	const char* msg;
};

class CORE_API CLog
{
public:
	static void Init();

	static void Destroy();

	static void LogMessage(ELogVerbosity verbosity, const char* msg, ...);

private:
	static void LogToIDE(const char* msg);

	static void LogToConsole(const char* msg, U8 color, bool isError = true);

	static void LogToFile(const char* msg);

	static void LogCrash(const char* msg);

private:
	static std::unique_ptr<IFileStream> m_logFile;
	static std::vector<LogEntry> m_logEntries;
};

#define GE_LOG(verbosity, msg, ...) CLog::LogMessage(verbosity, msg, __VA_ARGS__);