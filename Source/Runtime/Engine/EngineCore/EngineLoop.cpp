#include "EngineLoop.h"
#include "Engine.h"
#include "Platform/Interface/IPlatform.h"
#include "Platform/Interface/IApplication.h"

CEngineLoop::CEngineLoop()
{
	mApp = nullptr;
}

CEngineLoop::~CEngineLoop()
{
	Exit();
}

void CEngineLoop::Init()
{
	mApp = IPlatform::CreateApplication();

	FWindowDefintion windowDef;
	windowDef.title = "Sandbox";
	windowDef.width = 1920;
	windowDef.height = 1080;

	mApp->Init(windowDef);

	gEngine = new CEngine();
	gEngine->Init();
}

void CEngineLoop::Run()
{
	while (true)
	{
		mApp->HandleMessages();
		gEngine->Update();
	}
}

void CEngineLoop::Exit()
{
	gEngine->Destroy();
	delete gEngine;
	gEngine = nullptr;

	mApp->Exit();
	delete mApp;
	mApp = nullptr;
}