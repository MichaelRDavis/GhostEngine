#pragma once

#include "Core.h"

class IApplication;

struct SSystemInfo
{

};

class CORE_API ISystem
{
public:
	static IApplication* CreateApplication();

	static SSystemInfo GetSystemInfo();

	static void CreateConsole();

	static void DestroyConsole();

	static void DisplayMessageBox(const char* msg, const char* caption);

	static void PlayMessageBeep();
};