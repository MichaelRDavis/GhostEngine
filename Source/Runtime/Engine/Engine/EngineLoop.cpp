#include "EngineLoop.h"
#include "Engine.h"
#include "Platform/Interface/IPlatform.h"

CEngineLoop::CEngineLoop()
{
	mIsInitialised = false;
}

CEngineLoop::~CEngineLoop()
{
	Destroy();
}

void CEngineLoop::Init()
{
	gEngine = new CEngine();
	gEngine->Init();

	IPlatform::ConsoleWriteLine("Hello, World!");

	mIsInitialised = true;
}

void CEngineLoop::Update()
{
	while (mIsInitialised)
	{
		gEngine->Update();
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
}