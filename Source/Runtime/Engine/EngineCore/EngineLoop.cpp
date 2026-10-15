#include "EngineLoop.h"
#include "Engine.h"

CEngineLoop::CEngineLoop()
{
	
}

CEngineLoop::~CEngineLoop()
{
	DestroyEngine();
}

void CEngineLoop::InitializeEngine()
{
	gEngine = new CEngine();
	gEngine->Initialize();
}

void CEngineLoop::RunEngine()
{
	gEngine->Update();
}

void CEngineLoop::DestroyEngine()
{
	gEngine->Destroy();
}