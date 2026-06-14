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

bool CEngine::Init()
{
	mRenderer = new IRDI();
	if (!mRenderer->Init())
	{
		return false;
	}

	return true;
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