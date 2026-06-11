#pragma once

#include "CoreExport.h"
#include "Core.h"

typedef enum LogVerbosity
{
	Fatal,
	Error,
	Warning,
	Display,
	Log,
	Verbose,
	VeryVerbose
} LogVerbosity;

bool32 Log_Init();
void Log_Destroy();

CORE_API void Log_PrintMessage(LogVerbosity verbosity, const char* msg, ...);

#define GE_LOG(verbosity, msg, ...) Log_PrintMessage(verbosity, msg, ##__VA_ARGS__);