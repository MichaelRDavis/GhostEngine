#include "IEngine.h"

IEngine::IEngine()
{
	mRenderer = nullptr;
}

IEngine::~IEngine()
{
	Destroy();
}

void IEngine::Init(const SRenderViewport& viewport)
{
	mRenderer = new CVulkanRDI(viewport);
	mRenderer->Init();
}

void IEngine::Update(F64 deltaTime)
{
	mRenderer->Render(deltaTime);
}

void IEngine::Destroy()
{
	if (mRenderer != nullptr)
	{
		mRenderer->Destroy();
		delete mRenderer;
		mRenderer = nullptr;
	}
}