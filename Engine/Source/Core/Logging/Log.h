#pragma once

#include "Platform/Platform.h"

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

class CLog
{
public:
	static void Init();

	static void Destroy();

	static void LogMessage(ELogVerbosity verbosity, const char* msg, ...);

private:
	static void LogToIDE(const char* msg);

	static void LogToConsole(const char* msg, U8 color, bool isError = true);

	static void LogCrash(const char* msg);
};

#define GE_LOG(verbosity, msg, ...) CLog::LogMessage(verbosity, msg, __VA_ARGS__);