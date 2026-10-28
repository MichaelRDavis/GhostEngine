#pragma once

#include "System/SystemInterface/IApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication(const FWindowDescription& winDesc);
	~CWindowsApplication();

	void Init();
	void Run();
	void Destroy();

private:
	void HandleMessages();

	static LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	FWindowDescription mWindowDesc;

	HINSTANCE mAppInstance;
	HWND mWindowHandle;
	HMONITOR mMonitor;
};
#endif