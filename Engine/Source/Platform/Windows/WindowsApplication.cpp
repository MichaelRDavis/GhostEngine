#include "WindowsApplication.h"

CWindowsApplication::CWindowsApplication()
{
	m_instance = nullptr;
	m_windowHandle = nullptr;
	m_monitor = nullptr;
	m_description = { };
}

CWindowsApplication::~CWindowsApplication()
{
	Destroy();
}

void CWindowsApplication::Init(HINSTANCE instance)
{
	m_instance = instance;
	if (m_instance == nullptr)
	{
		m_instance = GetModuleHandleA(0);
	}
}

void CWindowsApplication::InitWindow(const WindowDescription& description)
{
	U32 winClassStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WNDCLASSEX windowClass = { };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = winClassStyle;
	windowClass.lpfnWndProc = WinProc;
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
	m_windowHandle = CreateWindowEx(
		0,
		L"WinAppClass",
		L"Sandbox",
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
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