#include "System/SystemOS/Interface/ISystem.h"

#ifdef GHOST_SYSTEM_WINDOWS
IApplication* ISystem::CreateApplication(const FWindowDescription& winDesc)
{
	return nullptr;
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