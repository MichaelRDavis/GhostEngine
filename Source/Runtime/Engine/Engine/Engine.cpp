#include "Engine.h"
#include "Renderer/IRDI.h"
#include "OpenGLRenderer/OpenGLRDI.h"
#include "VulkanRenderer/VulkanRDI.h"

CEngine::CEngine()
{
	mEngineConfig = {};
	mRenderer = nullptr;
}

CEngine::~CEngine()
{
	Destroy();
}

bool CEngine::Init(const EngineConfig& config, const ViewportInfo& viewport)
{
	mEngineConfig = config;

	if (mEngineConfig.graphicsAPI == EGraphicsAPI::OpenGL)
	{
		mRenderer = new COpenGLRDI();
	}
	else if (mEngineConfig.graphicsAPI == EGraphicsAPI::Vulkan)
	{
		mRenderer = new CVulkanRDI();
	}

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