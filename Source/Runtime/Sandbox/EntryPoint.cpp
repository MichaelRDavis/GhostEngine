#include "Core.h"

#ifdef GHOST_SYSTEM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{
	CLog::LogMessage("HelloWorld!");

	ITimer::Init();

	U64 num = 5;
	U64 newNum = 0;
	TArray<U64, 5> testArray;
	testArray.Add(num, 0);
	newNum = testArray.Remove(0);

	TDynamicArray<U64> testDynArray;

	FWindowDescription window;
	window.title = "Sandbox";
	window.width = 1920;
	window.height = 1080;
	window.positionX = 0;
	window.positionY = 0;
	window.mode = EWindowMode::Windowed;
	window.isActive = true;
	window.isHidden = false;

	IApplication* engineApp = ISystem::CreateApplication(window);
	engineApp->Init();

	float deltaTime = ITimer::GetAbsoluteTime();

	while (true)
	{
		engineApp->Run();
	}

	return 0;
}
#endif