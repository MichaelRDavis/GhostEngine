#pragma once

#include "Platform/Interface/IApplication.h"

#ifdef GHOST_PLATFORM_WINDOWS
class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	void Init(const FWindowDefintion& winDef);

	void Exit();

	void HandleMessages();

private:
	static LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE mAppInstance;
	HWND mWindowHandle;
};
#endif