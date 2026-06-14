#include "Engine/EngineLoop.h"

int main()
{
	CEngineLoop engineLoop;
	engineLoop.Init();
	engineLoop.Update();

	return 0;
}