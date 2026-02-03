#pragma once

#include "Renderer/RDI.h"
#include "Renderer/Vulkan/VulkanIncludes.h"

class CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	void Init(const Viewport& viewport);

	void Render();

	void Destroy();

private:
	void InitInstance();
	void DestroyInstance();

	void InitSurface();

	void InitDevice();
	void DestroyDevice();

private:
	Viewport m_viewport;

	VkInstance m_instance;
#ifdef _DEBUG
	VkDebugUtilsMessengerEXT m_debugCallback;
#endif
	I32 m_graphicsQueueIndex;
	VkPhysicalDevice m_gpu;

	VkSurfaceKHR m_surface;
};