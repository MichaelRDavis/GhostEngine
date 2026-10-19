#include "EngineCore/EngineLoop.h"

int main()
{
	CEngineLoop engineLoop;
	engineLoop.Init();
	engineLoop.Run();

	return 0;
}