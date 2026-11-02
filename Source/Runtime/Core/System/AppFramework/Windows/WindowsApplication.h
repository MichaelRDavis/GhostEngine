#pragma once

#include "Core.h"

#ifdef GHOST_SYSTEM_WINDOWS
class CWindowsApplication : public IApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	void MakeWindow(const SWindowDescription& winDesc);

	void Init();
	void Run();
	void Destroy();

	GHOST_INLINE static IWindow* GetWindow() { return mWindow; }

	GHOST_INLINE static const char* GetWIndowClassName() { return mWinClassName; }

	GHOST_INLINE HINSTANCE GetInstance() const { return mInstance; }

private:
	static LRESULT WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	static IWindow* mWindow;

	static const char* mWinClassName;

	HINSTANCE mInstance;
};
#endif