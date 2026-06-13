#pragma once

#include "CoreExport.h"

class CORE_API IPlatform
{
public:
	static void WriteToConsole(const char* msg);
};