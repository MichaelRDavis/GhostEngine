#include "WindowsApplication.h"

#ifdef GHOST_PLATFORM_WINDOWS
CWindowsApplication::CWindowsApplication()
{
	mAppInstance = nullptr;
	mWindowHandle = nullptr;
}

CWindowsApplication::~CWindowsApplication()
{
	Exit();
}

void CWindowsApplication::Init(const FWindowDefintion& winDef)
{
	mAppInstance = GetModuleHandleA(0);

	WNDCLASSA winClass = {};
	winClass.style = CS_DBLCLKS;
	winClass.lpfnWndProc = CWindowsApplication::WinProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hIcon = LoadIcon(mAppInstance, IDI_APPLICATION);
	winClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	winClass.hbrBackground = nullptr;
	winClass.lpszClassName = "WinAppClass";
	if (!RegisterClassA(&winClass))
	{
		MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	U32 clientX = 0;
	U32 clientY = 0;
	U32 clientWidth = winDef.width;
	U32 clientHeight = winDef.height;

	if (winDef.posX > 0 && winDef.posY > 0)
	{
		clientX = winDef.posX;
		clientY = winDef.posY;
	}
	else
	{
		clientX = CW_USEDEFAULT;
		clientY = CW_USEDEFAULT;
	}

	U32 winPosX = clientX;
	U32 winPosY = clientY;
	U32 winWidth = clientWidth;
	U32 winHeight = clientHeight;

	U32 winStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
	U32 winExStyle = WS_EX_APPWINDOW;

	winStyle |= WS_MAXIMIZEBOX;
	winStyle |= WS_MINIMIZEBOX;
	winStyle |= WS_THICKFRAME;

	RECT borderRect = {0,0,0,0};
	AdjustWindowRectEx(&borderRect, winStyle, 0, winExStyle);

	winPosX += borderRect.left;
	winPosY += borderRect.top;

	winWidth += borderRect.right - borderRect.left;
	winHeight += borderRect.bottom - borderRect.top;

	mWindowHandle = CreateWindowExA(
		winExStyle,
		"WinAppClass",
		winDef.title,
		winStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winWidth,
		winHeight,
		0,
		0,
		mAppInstance,
		0);
	if (mWindowHandle == nullptr)
	{
		MessageBoxA(0, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	bool shouldActivate = false;
	I32 showWindowFlag = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
	ShowWindow(mWindowHandle, showWindowFlag);
}

void CWindowsApplication::Exit()
{
	if (mWindowHandle != nullptr)
	{
		DestroyWindow(mWindowHandle);
		mWindowHandle = nullptr;
	}
}

void CWindowsApplication::HandleMessages()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

LRESULT CWindowsApplication::WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
#endif