#include "Platform/Platform.h"
#include "Core/Logging/Log.h"

#ifdef GE_WINDOWS_PLATFORM
#include "Platform/Windows/WindowsApplication.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	CWindowsApplication winApp;
	winApp.Init(hInstance);

	CLog::Init();

	GE_LOG(Fatal, "Hello, World!");
	GE_LOG(Error, "Hello, World!");
	GE_LOG(Warning, "Hello, World!");
	GE_LOG(Display, "Hello, World!");
	GE_LOG(Log, "Hello, World!");
	GE_LOG(Verbose, "Hello, World!");
	GE_LOG(VeryVerbose, "Hello, World!");

	WindowDescription winDesc;
	winApp.InitWindow(winDesc);
	winApp.HandleMessages();

	CLog::Destroy();

	return 0;
}
#endif