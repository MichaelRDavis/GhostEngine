#pragma once

#include "Core.h"

#ifdef GHOST_PLATFORM_WINDOWS
class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	void MakeWindow(const SWindowDescription& winDesc);

	void Init();
	void Run();
	void Destroy();

	GHOST_INLINE static const char* GetWindowClassName() { return mWinClassName; }
	GHOST_INLINE IWindow* GetWindow() { return mWindow; }
	GHOST_INLINE HINSTANCE GetInstance() const { return mInstance; }
	GHOST_INLINE bool IsAppRunning() { return mIsAppRunning; }

private:
	static LRESULT WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	static const char* mWinClassName;
	IWindow* mWindow;
	HINSTANCE mInstance;
	bool mIsAppRunning;
};
#endif