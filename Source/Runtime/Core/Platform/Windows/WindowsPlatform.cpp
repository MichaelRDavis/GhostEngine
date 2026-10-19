#include "Platform/Interface/IPlatform.h"
#ifdef GHOST_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsApplication.h"
#endif

#ifdef GHOST_PLATFORM_WINDOWS
IApplication* IPlatform::CreateApplication()
{
	return new CWindowsApplication();
}
#endif