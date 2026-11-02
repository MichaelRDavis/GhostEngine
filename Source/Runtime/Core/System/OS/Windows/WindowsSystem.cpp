#include "System/OS/Interface/ISystem.h"
#include "System/AppFramework/Windows/WindowsApplication.h"

#ifdef GHOST_SYSTEM_WINDOWS
IApplication* ISystem::CreateApplication()
{
	return new CWindowsApplication();
}

SSystemInfo ISystem::GetSystemInfo()
{
	SSystemInfo info;

	return info;
}

void ISystem::CreateConsole()
{
	AllocConsole();
}

void ISystem::DestroyConsole()
{
	FreeConsole();
}

void ISystem::DisplayMessageBox(const char* msg, const char* caption)
{
	MessageBoxA(nullptr, msg, caption, MB_ICONEXCLAMATION | MB_OK);
}

void ISystem::PlayMessageBeep()
{
	MessageBeep(MB_ICONSTOP);
}
#endif