#include "EngineLoop.h"
#include "Engine.h"
#include "Platform/Interface/IPlatform.h"
#include "ApplicationCore/Interface/IApplication.h"
#include "RendererCore/RendererTypes.h"

CEngineLoop::CEngineLoop()
{
	mApp = nullptr;
	mIsInitialised = false;
}

CEngineLoop::~CEngineLoop()
{
	Destroy();
}

void CEngineLoop::Init()
{
	ApplicationInfo appInfo;
	appInfo.appName = "Sandbox";
	appInfo.windowWidth = 1920;
	appInfo.windowHeight = 1080;
	appInfo.isWindowed = true;
	appInfo.hasConsole = true;
	appInfo.centerWindow = true;

	mApp = IPlatform::CreateApplication();
	if (!mApp->AppInit(appInfo))
	{
		return;
	}

	RenderViewport viewport;
	viewport.surface = mApp->GetWindowHandle();
	viewport.width = appInfo.windowWidth;
	viewport.height = appInfo.windowHeight;

	EngineConfig engineConfig;
	engineConfig.graphicsAPI = EGraphicsAPI::Opengl;

	gEngine = new CEngine();
	if (!gEngine->Init(engineConfig, viewport))
	{
		return;
	}

	mIsInitialised = true;
}

void CEngineLoop::Update()
{
	while (mIsInitialised && mApp->IsAppRunning())
	{
		gEngine->Update();
		mApp->AppRun();
	}
}

void CEngineLoop::Destroy()
{
	if (gEngine != nullptr)
	{
		gEngine->Destroy();
		delete gEngine;
		gEngine = nullptr;
	}

	if (mApp != nullptr)
	{
		mApp->AppExit();
		delete mApp;
		mApp = nullptr;
	}
}