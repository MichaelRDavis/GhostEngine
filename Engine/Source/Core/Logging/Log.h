#pragma once

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

	static void LogToConsole(const char* msg, bool isError = true);
};

#define GE_LOG(verbosity, msg, ...) CLog::LogMessage(verbosity, msg, __VA_ARGS__);