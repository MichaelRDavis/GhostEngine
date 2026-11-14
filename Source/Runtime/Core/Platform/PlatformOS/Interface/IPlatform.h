#pragma once

#include "Core.h"

class IApplication;

struct SPlatformInfo
{
	const char* cpuManufacturer;
	const char* cpuModel;
	const char* osName;
	U32 cpuClockSpeed;
	U32 cpuNumCores;
	U32 memoryAmount;
	bool is64Bit;
};

class CORE_API IPlatform
{
public:
	static IApplication* CreateApplication();

	static SPlatformInfo GetPlatformInfo();

	static void CreateConsole();

	static void DestroyConsole();

	static void DisplayMessageBox(const char* msg, const char* caption);

	static void Sleep(U64 ms);
};