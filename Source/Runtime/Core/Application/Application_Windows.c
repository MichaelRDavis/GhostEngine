#include "Application.h"

#ifdef GE_WINDOWS_PLATFORM
typedef struct FWindowsApplication
{
	HINSTANCE instance;
	HWND winHandle;
} FWindowsApplication;

LRESULT CALLBACK WndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

bool32 App_Init(FApplication* app, FWindowDefinition* winDef)
{
	app->application = malloc(sizeof(FWindowsApplication));
	app->winDefinition = winDef;
	FWindowsApplication* winApp = (FWindowsApplication*)app->application;

	winApp->instance = GetModuleHandleA(0);

	HICON icon = LoadIcon(winApp->instance, IDI_APPLICATION);
	WNDCLASSA windowClass;
	memset(&windowClass, 0, sizeof(windowClass));
	windowClass.style = CS_DBLCLKS;
	windowClass.lpfnWndProc = WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = winApp->instance;
	windowClass.hIcon = icon;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszClassName = "WindowsApplication";
	if (!RegisterClassA(&windowClass))
	{
		MessageBoxA(0, "Window registratinon failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	uint32 clientX = winDef->winPosX;
	uint32 clientY = winDef->winPosY;
	uint32 clientWidth = winDef->winWidth;
	uint32 clientHeight = winDef->winHeight;
	uint32 windowPosX = clientX;
	uint32 windowPosY = clientY;
	uint32 windowWidth = clientWidth;
	uint32 windowHeight = clientHeight;

	uint32 winStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
	uint32 winExStyle = WS_EX_APPWINDOW;
	winStyle |= WS_MAXIMIZEBOX;
	winStyle |= WS_MINIMIZEBOX;
	winStyle |= WS_THICKFRAME;

	RECT borderRect = {0,0,0,0};
	AdjustWindowRectEx(&borderRect, winStyle, 0, winExStyle);
	windowPosX += borderRect.left;
	windowPosY += borderRect.top;
	windowWidth += borderRect.right - borderRect.right;
	windowHeight += borderRect.bottom - borderRect.top;

	HWND handle = CreateWindowExA(
		winExStyle,
		"WindowsApplication",
		winDef->title,
		winStyle,
		windowPosX,
		windowPosY,
		windowWidth,
		windowHeight,
		0,
		0,
		winApp->instance,
		0);
	if (handle == NULL)
	{
		MessageBoxA(0, "Window creation failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	winApp->winHandle = handle;

	bool32 bShouldActivate = 1;
	int32 showWindowFlags = bShouldActivate ? SW_SHOW : SW_SHOWMINNOACTIVE;
	ShowWindow(winApp->winHandle, showWindowFlags);

	return TRUE;
}

void App_Run(FApplication* app)
{
	App_HandleMessages(app);
}

void App_Exit(FApplication* app)
{
	FWindowsApplication* winApp = (FWindowsApplication*)app->application;
	if (winApp->winHandle)
	{
		DestroyWindow(winApp->winHandle);
		winApp->winHandle = 0;
	}
}

bool32 App_HandleMessages(FApplication* app)
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ERASEBKGND:
		return 1;
	case WM_CLOSE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcA(hwnd, msg, wParam, lParam);
}
#endif