#pragma once

#include "Core.h"

class IApplication;

struct SSystemInfo
{
	const char* cpuManufacturer;
	const char* cpuModel;
	const char* osName;
	U32 cpuClockSpeed;
	U32 cpuNumCores;
	U32 memeoryAmount;
	bool is64Bit;
};

class CORE_API ISystem
{
public:
	static IApplication* CreateApplication();

	static SSystemInfo GetSystemInfo();

	static void CreateConsole();

	static void DestroyConsole();

	static void DisplayMessageBox(const char* msg, const char* caption);
};