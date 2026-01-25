#include "Platform/Platform.h"
#include "Engine/EngineLoop.h"

#ifdef GE_WINDOWS_PLATFORM
#include "Platform/Windows/WindowsApplication.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	CWindowsApplication winApp;
	winApp.Init(hInstance);

	CEngineLoop engineLoop(winApp);
	engineLoop.Init();
	engineLoop.Run();

	return 0;
}
#endif