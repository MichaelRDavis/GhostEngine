#pragma once

#include "CoreExport.h"
#include "Core.h"

class CORE_API IFileSystem
{
public:
	static std::vector<char> ReadFile(const char* path);
};