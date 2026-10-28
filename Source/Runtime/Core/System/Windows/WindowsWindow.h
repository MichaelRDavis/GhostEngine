#pragma once

#include "System/SystemInterface/IWindow.h"

#ifdef GHOST_SYSTEM_WINDOWS
class CWindowsWindow : public IWindow
{
public:
	CWindowsWindow();
	~CWindowsWindow();

	void Init();
	void Destroy();

	void* GetWindowHandle() const;

private:
	HWND mWindowHandle;
};
#endif