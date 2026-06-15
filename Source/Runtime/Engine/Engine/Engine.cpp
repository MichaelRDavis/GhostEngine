#include "Engine.h"
#include "Renderer/IRDI.h"

CEngine::CEngine()
{
	mEngineConfig = {};
	mRenderer = nullptr;
}

CEngine::~CEngine()
{
	Destroy();
}

bool CEngine::Init(const EngineConfig& config, const RenderViewport& viewport)
{
	mEngineConfig = config;

	mRenderer = new IRDI();
	if (!mRenderer->Init(viewport))
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