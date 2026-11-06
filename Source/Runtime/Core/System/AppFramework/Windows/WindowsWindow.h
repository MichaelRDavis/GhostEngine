#pragma once

#include "Core.h"

#ifdef GHOST_SYSTEM_WINDOWS
class CWindowsApplication;

class CWindowsWindow : public IWindow
{
public:
	CWindowsWindow(IApplication* appOwner, const SWindowDescription& winDesc);
	~CWindowsWindow();

	void Init();
	void Destroy();

	GHOST_INLINE void* GetWindowHandle() const { return mWindowHandle; }

private:
	CWindowsApplication* mAppOwner;
	SWindowDescription mWinDesc;
	HWND mWindowHandle;
};
#endif