#include "Engine.h"
#include "Renderer/Vulkan/Core/VulkanRDI.h"

CEngine::CEngine()
{
	m_renderer = nullptr;
}

CEngine::~CEngine()
{
	Destroy();
}

void CEngine::Init()
{
	// TODO: Check for Vulkan support
	m_renderer = new CVulkanRDI();
	m_renderer->Init();
}

void CEngine::Update(F32 deltaTime)
{
	m_renderer->Render();
}

void CEngine::Destroy()
{
	if (m_renderer != nullptr)
	{
		m_renderer->Destroy();
		delete m_renderer;
		m_renderer = nullptr;
	}
}

extern CEngine* gEngine = nullptr;

extern CEngine* GetEngine()
{
	GE_CHECK(gEngine);

	if (gEngine != nullptr)
	{
		return gEngine;
	}

	return nullptr;
}