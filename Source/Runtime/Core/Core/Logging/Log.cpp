#include "Log.h"

void CLog::Init()
{

}

void CLog::Destroy()
{

}

void CLog::Clear()
{

}

void CLog::LogMessage(const char* msg)
{
#ifdef GHOST_SYSTEM_WINDOWS
	DWORD length = strlen(msg);
	LPDWORD numWritten = 0;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), msg, length, numWritten, 0);
#endif
}