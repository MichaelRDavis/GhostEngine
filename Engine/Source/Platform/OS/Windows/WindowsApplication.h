#pragma once

#include "Platform/OS/Interface/IApplication.h"

#ifdef GE_WINDOWS_PLATFORM
class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	void Init();

	void InitWindow(const WindowDescription& description);

	void HandleMessages();

	void Destroy();

	GE_INLINE void* GetWindowHandle() const { return m_windowHandle; }

private:
	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_instance;
	HMONITOR m_monitorHandle;
	MONITORINFO m_monitorInfo;
	HWND m_windowHandle;
	WindowDescription m_description;
};
#endif