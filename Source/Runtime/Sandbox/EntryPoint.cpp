#include "Core.h"

#ifdef GHOST_SYSTEM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
{
	ISystem::CreateConsole();

	TArray<U64, 10> testAry;
	TDynamicArray<U64> testDynAry;

	TUniquePointer<CGameObject> object1 = MakeUnique<CGameObject>();
	TSharedPointer<CGameObject> object2 = MakeShared<CGameObject>();

	SWindowDescription windowDesc;
	windowDesc.title = "Sandbox";
	windowDesc.width = 1920;
	windowDesc.height = 1080;
	windowDesc.windowMode = EWindowMode::Windowed;
	windowDesc.isActive = true;
	windowDesc.isHidden = false;

	IApplication* sandboxApp = ISystem::CreateApplication();
	sandboxApp->Init();
	sandboxApp->MakeWindow(windowDesc);

	while (true)
	{
		sandboxApp->Run();
	}

	return 0;
}
#endif