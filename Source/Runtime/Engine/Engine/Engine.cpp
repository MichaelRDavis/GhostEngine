#include "Engine.h"
#include "Renderer/IRDI.h"

CEngine::CEngine()
{
	mRenderer = nullptr;
}

CEngine::~CEngine()
{
	Destroy();
}

void CEngine::Init()
{
	mRenderer = new IRDI();
	mRenderer->Init();
}

void CEngine::Update()
{
	
}

void CEngine::Destroy()
{
	if (mRenderer != nullptr)
	{
		mRenderer->Destroy();
		delete mRenderer;
		mRenderer = nullptr;
	}
}