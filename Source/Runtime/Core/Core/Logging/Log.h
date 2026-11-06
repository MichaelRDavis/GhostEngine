#pragma once

#include "Core.h"

enum ELogVerbosity
{
	Fatal,
	Error,
	Warning,
	Info,
	Log,
	Verbose,
	VeryVerbose
};

struct SLogEntry
{
	const char* category;
	const char* msg;
	ELogVerbosity verbosity;
	U64 localTime;
};

class CORE_API CLog
{
public:
	static void Init();

	static void Destroy();

	static void Clear();

	static void LogMessage(ELogVerbosity verbosity, const char* msg, ...);

private:
	static void LogMessageToConsole(ELogVerbosity verbosity, const char* msg, bool isError = false);

	static void LogMessageToIDE(const char* msg);

private:
	static std::vector<SLogEntry> mLogEntries;
};

#define GHOST_LOG(verbosity, msg, ...) CLog::LogMessage(verbosity, msg, __VA_ARGS__)