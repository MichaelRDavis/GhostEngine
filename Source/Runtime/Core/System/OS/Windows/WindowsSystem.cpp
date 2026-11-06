#include "System/OS/Interface/ISystem.h"
#include "System/AppFramework/Windows/WindowsApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
IApplication* ISystem::CreateApplication()
{
	return new CWindowsApplication();
}

SSystemInfo ISystem::GetSystemInfo()
{
	SSystemInfo info {};

	I32 cpuInfo[4] = {-1};
	__cpuid(cpuInfo, 0);
	info.cpuManufacturer = (char*)malloc(8);
	memcpy((char*)info.cpuManufacturer, &cpuInfo[1], 4);
	memcpy((char*)info.cpuManufacturer + 4, &cpuInfo[3], 4);
	memcpy((char*)info.cpuManufacturer + 8, &cpuInfo[2], 4);

	char brandString[48];
	__cpuid(cpuInfo, 0x80000000);
	U32 extensionIDcount = cpuInfo[0];
	for (U32 i = 0x80000000; i <= extensionIDcount; ++i)
	{
		__cpuid(cpuInfo, i);
		if (i == 0x80000002)
		{
			memcpy(brandString, cpuInfo, sizeof(cpuInfo));
		}
		else if (i == 0x80000003)
		{
			memcpy(brandString + 16, cpuInfo, sizeof(cpuInfo));
		}
		else if (i == 0x80000004)
		{
			memcpy(brandString + 32, cpuInfo, sizeof(cpuInfo));
		}
	}

	info.cpuModel = brandString;

	SYSTEM_INFO sysInfo;
	::GetSystemInfo(&sysInfo);
	info.cpuNumCores = sysInfo.dwNumberOfProcessors;

	HKEY key;
	long status = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &key);
	if (status == ERROR_SUCCESS)
	{

	}

	return info;
}

void ISystem::CreateConsole()
{
	AllocConsole();
}

void ISystem::DestroyConsole()
{
	FreeConsole();
}

void ISystem::DisplayMessageBox(const char* msg, const char* caption)
{
	MessageBoxA(nullptr, msg, caption, MB_ICONEXCLAMATION | MB_OK);
}
#endif