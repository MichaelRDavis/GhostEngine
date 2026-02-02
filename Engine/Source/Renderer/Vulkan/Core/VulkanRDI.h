#pragma once

#include "Renderer/RDI.h"
#include "Renderer/Vulkan/VulkanIncludes.h"

class CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	void Init();

	void Render();

	void Destroy();

private:
	void InitInstance();
	void DestroyInstance();

	void InitDevice();
	void DestroyDevice();

private:
	VkInstance m_instance;
#ifdef _DEBUG
	VkDebugUtilsMessengerEXT m_debugCallback;
#endif
};