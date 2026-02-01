#include "Platform/OS/Interface/IPlatform.h"

#ifdef GE_WINDOWS_PLATFORM
void IPlatform::Sleep(U32 ms)
{
	::Sleep(ms);
}

PlatformInfo IPlatform::GetPlatformInfo()
{
	PlatformInfo info = { };

	// Get CPU clock speed
	HKEY regKey;
	if (RegOpenKeyEx
		(HKEY_LOCAL_MACHINE,
		L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		0,
		KEY_READ,
		&regKey) == ERROR_SUCCESS)
	{
		DWORD mhz;
		DWORD bufferSize = 4;
		RegQueryValueEx(regKey, L"~MHz", nullptr, nullptr, (LPBYTE)&mhz, &bufferSize);
		info.cpuClockSpeed = (U32)mhz;
	}

	// Get CPU core count
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	info.cpuCores = (U32)sysInfo.dwNumberOfProcessors;

	// Get physical memory amount
	MEMORYSTATUSEX memStatus;
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memStatus);
	info.memory = (U32)(memStatus.ullTotalPhys / (1024 * 1024));

	// Is OS 64-bit
#if defined(__x86_64__) || defined(_M_X64)
	info.is64Bit = true;
#else
	info.is64Bit = false;
#endif

	return info;
}
#endif