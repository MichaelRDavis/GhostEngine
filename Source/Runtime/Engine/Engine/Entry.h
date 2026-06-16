#pragma once

#include "Engine/EngineLoop.h"

#ifdef _WIN64
int main()
{
	CEngineLoop engineLoop;
	engineLoop.Init();
	engineLoop.Update();

	return 0;
}
#endif