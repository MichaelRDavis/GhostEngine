#pragma once

#include "CoreHeader.h"

class IApplication;

class CORE_API IPlatform
{
public:
	static IApplication* CreateApplication();
};