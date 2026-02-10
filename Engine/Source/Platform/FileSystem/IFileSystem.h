#pragma once

#include "Platform/Platform.h"

class IFileSystem
{
public:
	static std::vector<char> ReadFile(const char* path);
};