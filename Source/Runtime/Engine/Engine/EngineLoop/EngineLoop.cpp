#include "EngineLoop.h"

CEngineLoop::CEngineLoop()
{
	mEngineApp = nullptr;
}

CEngineLoop::~CEngineLoop()
{
	EngineExit();
}

void CEngineLoop::EngineInit()
{
	CLog::Init();

#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_DEBUG_GAME)
	ISystem::CreateConsole();
#endif
	
	SSystemInfo sysInfo = ISystem::GetSystemInfo();
	GHOST_LOG(Log, "%s", sysInfo.cpuManufacturer);
	GHOST_LOG(Log, "%s", sysInfo.cpuModel);

	SWindowDescription windowDesc;
#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_RELEASE_EDITOR)
	windowDesc.title = "Sandbox Editor";
	windowDesc.width = 1920;
	windowDesc.height = 1080;
	windowDesc.windowMode = EWindowMode::Windowed;
	windowDesc.isActive = true;
	windowDesc.isHidden = false;
#elif defined(GHOST_DEBUG_GAME) || defined(GHOST_RELEASE_GAME)
	windowDesc.title = "Ghost Game";
	windowDesc.windowMode = EWindowMode::Fullscreen;
	windowDesc.isActive = true;
	windowDesc.isHidden = false;
#endif

	mEngineApp = ISystem::CreateApplication();
	mEngineApp->Init();
	mEngineApp->MakeWindow(windowDesc);
}

void CEngineLoop::EngineUpdate()
{
	while (true)
	{
		mEngineApp->Run();
	}
}

void CEngineLoop::EngineExit()
{
	if (mEngineApp != nullptr)
	{
		mEngineApp->Destroy();
		delete mEngineApp;
		mEngineApp = nullptr;
	}

	CLog::Destroy();
}