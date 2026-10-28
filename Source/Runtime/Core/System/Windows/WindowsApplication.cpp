#include "WindowsApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
CWindowsApplication::CWindowsApplication(const FWindowDescription& winDesc)
	: IApplication(winDesc)
{
	mWindowDesc = winDesc;
	mAppInstance = nullptr;
	mWindowHandle = nullptr;
	mMonitor = nullptr;
}

CWindowsApplication::~CWindowsApplication()
{
	Destroy();
}

void CWindowsApplication::Init()
{
	mAppInstance = GetModuleHandleA(0);

	WNDCLASSA windowClass = {};
	windowClass.style = CS_DBLCLKS;
	windowClass.lpfnWndProc = CWindowsApplication::WinProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = mAppInstance;
	windowClass.hIcon = LoadIcon(mAppInstance, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(mAppInstance, IDC_ARROW);
	windowClass.hbrBackground = nullptr;
	windowClass.lpszClassName = "WinAppClass";
	if (!RegisterClassA(&windowClass))
	{	
		MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	U32 clientPosX = mWindowDesc.positionX;
	U32 clientPosY = mWindowDesc.positionY;
	U32 windowPosX = clientPosX;
	U32 windowPosY = clientPosY;

	U32 clientWidth = mWindowDesc.width;
	U32 clientHeight = mWindowDesc.height;
	U32 windowWidth = clientWidth;
	U32 windowHeight = clientHeight;

	U32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
	windowStyle |= WS_MAXIMIZEBOX;
	windowStyle |= WS_MINIMIZEBOX;
	windowStyle |= WS_THICKFRAME;
	U32 windowExStyle = WS_EX_APPWINDOW;

	RECT borderRect = {0,0,0,0};
	AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);
	windowPosX += borderRect.left;
	windowPosY += borderRect.top;
	windowWidth += borderRect.right - borderRect.left;
	windowHeight += borderRect.bottom - borderRect.top;

	mWindowHandle = CreateWindowExA(
		windowExStyle,
		"WinAppClass",
		mWindowDesc.title,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		0,
		0,
		mAppInstance,
		0);
	if (mWindowHandle == nullptr)
	{
		MessageBoxA(0, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	I32 showWindowFlag = mWindowDesc.isActive ? SW_SHOW : SW_SHOWMINNOACTIVE;
	ShowWindow(mWindowHandle, showWindowFlag);
}

void CWindowsApplication::Run()
{
	HandleMessages();
}

void CWindowsApplication::Destroy()
{
	if (mWindowHandle != nullptr)
	{
		DestroyWindow(mWindowHandle);
		mWindowHandle = nullptr;
	}
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

LRESULT CWindowsApplication::WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
#endif