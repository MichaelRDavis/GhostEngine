#pragma once

#include "Core.h"

enum class ELogVerbosity
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

	static void LogMessage(const char* msg);
};