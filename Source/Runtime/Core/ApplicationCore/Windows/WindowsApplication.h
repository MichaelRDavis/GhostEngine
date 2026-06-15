#pragma once

#include "ApplicationCore/Interface/IApplication.h"

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	bool AppInit(const ApplicationInfo& appInfo);
	void AppRun();
	void AppExit();

	inline void* GetWindowHandle() const
	{
		return mWindowHandle;
	}

private:
	void HandleMessages();

private:
	ApplicationInfo mAppInfo;

	HINSTANCE mInstance;
	HWND mWindowHandle;
};
#endif