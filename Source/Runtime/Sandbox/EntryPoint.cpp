#include "Core.h"

#ifdef GHOST_SYSTEM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{
	ISystem::CreateConsole();
	CLog::LogMessage("Hello, Game Engine!");
	ISystem::DisplayMessageBox("Hello, Game Engine!", "Sandbox Error");

	while (true)
	{
		
	}

	return 0;
}
#endif