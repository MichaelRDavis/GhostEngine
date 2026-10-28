#pragma once

#include "Core.h"

struct FWindowDescription;
class IApplication;

class CORE_API ISystem
{
public:
	static IApplication* CreateApplication(const FWindowDescription& winDesc);

	static void CreateConsole();

	static void DestroyConsole();

	static void DisplayMessageBox(const char* msg, const char* caption);

	static void PlayMessageBeep();
};