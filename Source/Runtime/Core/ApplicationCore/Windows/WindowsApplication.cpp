#include "WindowsApplication.h"
#include <cstdio>

#ifdef _WIN64
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

CWindowsApplication::CWindowsApplication()
{
	mAppInfo = {};
	mInstance = nullptr;
	mWindowHandle = nullptr;
}

CWindowsApplication::~CWindowsApplication()
{
	AppExit();
}

bool CWindowsApplication::AppInit(const ApplicationInfo& appInfo)
{
	mAppInfo = appInfo;

	mInstance = GetModuleHandleA(0);
	HICON icon = LoadIcon(mInstance, IDI_APPLICATION);
	HCURSOR cursor = LoadCursor(mInstance, IDC_ARROW);

	WNDCLASSA windowClass = {};
	windowClass.style = CS_DBLCLKS;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = mInstance;
	windowClass.hIcon = icon;
	windowClass.hCursor = cursor;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszClassName = "WindowClass";
	if (!RegisterClassA(&windowClass))
	{
		MessageBoxA(0, "Window Class registration failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	if (mAppInfo.hasConsole)
	{
		SetConsoleTitleA(mAppInfo.appName);
	}

	if (mAppInfo.isWindowed)
	{
		int clientX = mAppInfo.windowPosX;
		int clientY = mAppInfo.windowPosY;
		int clientWidth = mAppInfo.windowWidth;
		int clientHeight = mAppInfo.windowHeight;

		if (clientX == 0 && clientY == 0)
		{
			clientX = CW_USEDEFAULT;
			clientY = CW_USEDEFAULT;
		}

		int winPosX = clientX;
		int winPosY = clientY;
		int winWidth = clientWidth;
		int winHeight = clientHeight;

		int windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		int windowExStyle = WS_EX_APPWINDOW;

		windowStyle |= WS_MAXIMIZEBOX;
		windowStyle |= WS_MINIMIZEBOX;
		windowStyle |= WS_THICKFRAME;

		RECT borderRect = {0,0,0,0};
		AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);

		winPosX += borderRect.left;
		winPosY += borderRect.top;
		winWidth += borderRect.right - borderRect.left;
		winHeight += borderRect.bottom - borderRect.top;

		mWindowHandle = CreateWindowExA(
			windowExStyle,
			"WindowClass",
			mAppInfo.appName,
			windowStyle,
			winPosX,
			winPosY,
			winWidth,
			winHeight,
			0,
			0,
			mInstance,
			0);
		if (mWindowHandle == nullptr)
		{
			MessageBoxA(0, "Window creation failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		bool shouldActivate = true;
		int showWindowFlag = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
		ShowWindow(mWindowHandle, showWindowFlag);
	}

	mIsAppRunning = true;
	return true;
}

void CWindowsApplication::AppRun()
{
	HandleMessages();
}

void CWindowsApplication::AppExit()
{
	
}

void CWindowsApplication::HandleMessages()
{
	MSG message;
	while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
#endif