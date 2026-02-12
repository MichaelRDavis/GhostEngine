#pragma once

#include "Core.h"
#include "EngineLoop.h"

#ifdef GE_WINDOWS_PLATFORM
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	CEngineLoop engineLoop;
	engineLoop.Init();
	engineLoop.Run();

	return 0;
}
#endif