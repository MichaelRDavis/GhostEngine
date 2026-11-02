#include "WindowsWindow.h"
#include "WindowsApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
CWindowsWindow::CWindowsWindow(IApplication* appOwner, const SWindowDescription& winDesc)
	: IWindow(appOwner, winDesc)
{
	mAppOwner = (CWindowsApplication*)appOwner;
	mWinDesc = winDesc;
	mWindowHandle = nullptr;
}

CWindowsWindow::~CWindowsWindow()
{
	Destroy();
}

void CWindowsWindow::Init()
{
	U32 clientPosX = mWinDesc.positionX;
	U32 clientPosY = mWinDesc.positionY;
	U32 windowPosX = clientPosX;
	U32 windowPosY = clientPosY;

	U32 clientWidth = mWinDesc.width;
	U32 clientHeight = mWinDesc.height;
	U32 windowWidth = clientWidth;
	U32 windowHeight = clientHeight;

	U32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
	U32 windowExStyle = WS_EX_APPWINDOW;

	windowStyle |= WS_MAXIMIZEBOX;
	windowStyle |= WS_MINIMIZEBOX;
	windowStyle |= WS_THICKFRAME;

	RECT borderRect = {0,0,0,0};
	AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);

	mWindowHandle = CreateWindowExA(
		windowExStyle,
		mAppOwner->GetWIndowClassName(),
		mWinDesc.title,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		0,
		0,
		mAppOwner->GetInstance(),
		0);
	if (mWindowHandle == nullptr)
	{
		MessageBoxA(0, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	I32 showWindowFlag = mWinDesc.isActive ? SW_SHOW : SW_SHOWMINNOACTIVE;
	ShowWindow(mWindowHandle, showWindowFlag);
}	

void CWindowsWindow::Destroy()
{
	if (mWindowHandle != nullptr)
	{
		DestroyWindow(mWindowHandle);
		mWindowHandle = nullptr;
	}
}
#endif