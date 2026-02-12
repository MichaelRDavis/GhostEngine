#include "IEngine.h"
#include "Vulkan/Core/VulkanRDI.h"

IEngine::IEngine()
{
	m_renderer = nullptr;
}

IEngine::~IEngine()
{
	Destroy();
}

void IEngine::Init(const Viewport& viewport)
{
	// TODO: Check for Vulkan support
	m_renderer = new CVulkanRDI();
	m_renderer->Init(viewport);
}

void IEngine::Update(F32 deltaTime)
{
	m_renderer->Render(deltaTime);
}

void IEngine::Destroy()
{
	if (m_renderer != nullptr)
	{
		m_renderer->Destroy();
		delete m_renderer;
		m_renderer = nullptr;
	}
}

extern IEngine* gEngine = nullptr;

extern IEngine* GetEngine()
{
	GE_CHECK(gEngine);

	if (gEngine != nullptr)
	{
		return gEngine;
	}

	return nullptr;
}