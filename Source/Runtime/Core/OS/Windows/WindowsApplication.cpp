#include "WindowsApplication.h"

#ifdef GE_WINDOWS_PLATFORM
CWindowsApplication::CWindowsApplication()
{
	m_instance = nullptr;
	m_monitorHandle = nullptr;
	m_monitorInfo = { };
	m_windowHandle = nullptr;
	m_description = { };
}

CWindowsApplication::~CWindowsApplication()
{
	Destroy();
}

void CWindowsApplication::Init()
{
	if (m_instance == nullptr)
	{
		m_instance = GetModuleHandleA(0);
	}

#ifdef _DEBUG
	AllocConsole();
	SetConsoleTitleA("Sandbox Console");
#endif

	const POINT anchorPoint = { 0, 0 };
	m_monitorHandle = MonitorFromPoint(anchorPoint, MONITOR_DEFAULTTOPRIMARY);

	memset(&m_monitorInfo, 0, sizeof(MONITORINFO));
	m_monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(m_monitorHandle, &m_monitorInfo);
}

void CWindowsApplication::InitWindow(const WindowDescription& description)
{
	m_description = description;

	U32 winClassStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WNDCLASSEX windowClass = { };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = winClassStyle;
	windowClass.lpfnWndProc = CWindowsApplication::WinProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = m_instance;
	windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = L"WinAppClass";
	windowClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	if (!RegisterClassEx(&windowClass))
	{
		MessageBoxA(nullptr, "Window registration failed!", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}

	U32 windowStyle = WS_OVERLAPPEDWINDOW;
	if (description.windowMode == EWindowMode::Fullscreen)
	{
		windowStyle |= WS_MAXIMIZE;
	}

	I32 width = 0;
	I32 height = 0;
	if (description.windowMode == EWindowMode::Fullscreen)
	{
		width = m_monitorInfo.rcWork.right - m_monitorInfo.rcWork.left;
		height = m_monitorInfo.rcWork.bottom - m_monitorInfo.rcWork.top;
	}
	else if (description.windowMode == EWindowMode::Windowed)
	{
		RECT rect;
		SetRect(&rect, 0, 0, description.width, description.height);
		AdjustWindowRect(&rect, windowStyle, false);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	m_windowWidth = width;
	m_windowHeight = height;

	m_windowHandle = CreateWindowEx(
		0,
		L"WinAppClass",
		L"Sandbox",
		windowStyle,
		m_windowWidth,
		m_windowHeight,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		nullptr,
		m_instance,
		nullptr);
	if (m_windowHandle == nullptr)
	{
		MessageBoxA(nullptr, "Window creation failed!", "Error", MB_ICONERROR | MB_OKCANCEL);
		return;
	}

	ShowWindow(m_windowHandle, SW_SHOW);
}

void CWindowsApplication::HandleMessages()
{
	MSG msg = { };
	while (GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CWindowsApplication::Destroy()
{
	if (m_windowHandle != nullptr)
	{
		DestroyWindow(m_windowHandle);
		m_windowHandle = nullptr;
	}

#ifdef _DEBUG
	FreeConsole();
#endif
}

LRESULT CWindowsApplication::WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
#endif