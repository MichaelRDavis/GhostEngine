#pragma once

#include "Platform/Platform.h"

struct PlatformInfo
{
	const char* osName;
	U32 cpuClockSpeed;
	U32 cpuCores;
	U32 memory;
	bool is64Bit;
};

class IPlatform
{
public:
	static void Sleep(U32 ms);

	static PlatformInfo GetPlatformInfo();

	static std::vector<char> ReadFile(const char* path);
};