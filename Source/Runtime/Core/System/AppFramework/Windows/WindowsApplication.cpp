#include "WindowsApplication.h"
#include "WindowsWindow.h"

#ifdef GHOST_SYSTEM_WINDOWS
IWindow* CWindowsApplication::mWindow = nullptr;
const char* CWindowsApplication::mWinClassName = "Win32Application";

CWindowsApplication::CWindowsApplication()
{
	mInstance = nullptr;
}

CWindowsApplication::~CWindowsApplication()
{
	Destroy();
}

void CWindowsApplication::MakeWindow(const SWindowDescription& winDesc)
{
	mWindow = new CWindowsWindow(this, winDesc);
	mWindow->Init();
}

void CWindowsApplication::Init()
{
	mInstance = GetModuleHandleA(0);

	U64 winClassStyle = CS_DBLCLKS;

	WNDCLASSA windowClass {};
	windowClass.style = winClassStyle;
	windowClass.lpfnWndProc = CWindowsApplication::WinProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = mInstance;
	windowClass.hIcon = LoadIcon(mInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(mInstance, IDC_ARROW);
	windowClass.hbrBackground = nullptr;
	windowClass.lpszClassName = CWindowsApplication::mWinClassName;
	if (!RegisterClassA(&windowClass))
	{
		MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
}

void CWindowsApplication::Run()
{
	MSG msg;

	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

void CWindowsApplication::Destroy()
{
	if (mWindow != nullptr)
	{
		mWindow->Destroy();
		delete mWindow;
		mWindow = nullptr;
	}
}

LRESULT CWindowsApplication::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			mWindow->Destroy();
			break;
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}
#endif