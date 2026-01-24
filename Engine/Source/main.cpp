#include "Platform/Platform.h"

#ifdef GE_WINDOWS_PLATFORM
#include "Platform/Windows/WindowsApplication.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	CWindowsApplication winApp;
	winApp.Init(hInstance);

	WindowDescription winDesc;
	winApp.InitWindow(winDesc);

	while (true)
	{
		winApp.HandleMessages();
	}

	return 0;
}
#endif