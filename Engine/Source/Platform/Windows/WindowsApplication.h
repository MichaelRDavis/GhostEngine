#pragma once

#include "Platform/Platform.h"

enum class EWindowMode
{
	Fullscreen,
	Windowed
};

struct WindowDescription
{
	const wchar_t* title;
	I32 width;
	I32 height;
	I32 posX;
	I32 posY;
	EWindowMode windowMode;
	bool isHidden;

	WindowDescription()
	{
		title = L"\0";
		width = 1920;
		height = 1080;
		posX = 0;
		posY = 0;
		windowMode = EWindowMode::Fullscreen;
		isHidden = false;
	}
};

class CWindowsApplication
{
public:
	CWindowsApplication();
	~CWindowsApplication();

	void Init(HINSTANCE instance);

	void InitWindow(const WindowDescription& description);

	void HandleMessages();

	void Destroy();

private:
	static LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE m_instance;
	HMONITOR m_monitorHandle;
	MONITORINFO m_monitorInfo;
	HWND m_windowHandle;
	WindowDescription m_description;
};