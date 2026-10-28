#include "WindowsWindow.h"

CWindowsWindow::CWindowsWindow()
{
	mWindowHandle = nullptr;
}

CWindowsWindow::~CWindowsWindow()
{
	Destroy();
}

void CWindowsWindow::Init()
{

}

void CWindowsWindow::Destroy()
{

}

void* CWindowsWindow::GetWindowHandle() const
{
	return mWindowHandle;
}
