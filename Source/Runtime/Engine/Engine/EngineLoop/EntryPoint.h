#pragma once

#include "Engine.h"

#ifdef GHOST_PLATFORM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CEngineLoop engineLoop;
	engineLoop.EngineInit();
	engineLoop.EngineUpdate();

	return 0;
}
#endif