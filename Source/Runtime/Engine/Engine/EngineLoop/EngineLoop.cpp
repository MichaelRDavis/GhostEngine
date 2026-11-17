#include "EngineLoop.h"
#include "Engine/EngineFramework/GameEngine.h"
#include "Engine/EngineFramework/SandboxEngine.h"

CEngineLoop::CEngineLoop()
{
	mEngineApp = nullptr;
	mIsEngineRunning = false;
}

CEngineLoop::~CEngineLoop()
{
	EngineExit();
}

void CEngineLoop::EngineInit()
{
	ITime::StartTimer();
	CLog::Init();

#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_DEBUG_GAME)
	IPlatform::CreateConsole();
#endif
	
	SPlatformInfo info = IPlatform::GetPlatformInfo();
	GHOST_LOG(Log, "CPU: %s", info.cpuManufacturer);
	GHOST_LOG(Log, "CPU: %s", info.cpuModel);
	GHOST_LOG(Log, "CPU: %d", info.cpuNumCores);

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

	mEngineApp = IPlatform::CreateApplication();
	mEngineApp->Init();
	mEngineApp->MakeWindow(windowDesc);

#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_RELEASE_EDITOR)
	gEngine = new CSandboxEngine();
#elif defined(GHOST_DEBUG_GAME) || defined(GHOST_RELEASE_GAME)
	gEngine = new CGameEngine();
#endif

	SRenderViewport viewport;
	viewport.viewportWidth = windowDesc.width;
	viewport.viewportHeight = windowDesc.height;
	viewport.windowHandle = mEngineApp->GetWindow()->GetWindowHandle();

	gEngine->Init(viewport);

	mIsEngineRunning = true;
}

void CEngineLoop::EngineUpdate()
{
	F64 deltaTime = ITime::GetAbsoluteTime();

	while (mIsEngineRunning && mEngineApp->IsAppRunning())
	{
		mEngineApp->Run();
		gEngine->Update(deltaTime);
	}
}

void CEngineLoop::EngineExit()
{
	mIsEngineRunning = false;

	if (gEngine != nullptr)
	{
		gEngine->Destroy();
		delete gEngine;
		gEngine = nullptr;
	}

	if (mEngineApp != nullptr)
	{
		mEngineApp->Destroy();
		delete mEngineApp;
		mEngineApp = nullptr;
	}

	CLog::Destroy();
}

IEngine* gEngine = nullptr;

IEngine* GetEngine()
{
	return gEngine;
}