#include "Log.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

const char* verbosityStrings [7] =
{
	"[Fatal]: ",
	"[Error]: ",
	"[Warning]: ",
	"[Display]: ",
	"[Log]: ",
	"[Verbose]: ",
	"[VeryVerbose]: "
};

bool32 Log_Init()
{
   return TRUE;
}

void Log_Destroy()
{
	
}

CORE_API void Log_PrintMessage(LogVerbosity verbosity, const char* msg, ...)
{
	char outMsg[32000];
	memset(outMsg, 0, sizeof(outMsg));

#ifdef _MSC_VER
	va_list argPtr;
#else 
	__builtin_va_list argPtr;
#endif
	
	va_start(argPtr, outMsg);
	vsnprintf(outMsg, 32000, msg, argPtr);
	va_end(argPtr);

	char msgBuffer[32000];
	sprintf(msgBuffer, "%s%s\n", verbosityStrings[verbosity], outMsg);

	switch (verbosity)
	{
	case Fatal:
		printf("%s", msgBuffer);
		break;
	case Error:
		printf("%s", msgBuffer);
		break;
	case Warning:
		printf("%s", msgBuffer);
		break;
	case Display:
		printf("%s", msgBuffer);
		break;
	case Log:
		printf("%s", msgBuffer);
		break;
	case Verbose:
		printf("%s", msgBuffer);
		break;
	case VeryVerbose:
		printf("%s", msgBuffer);
		break;
	default:
		break;
	}
}