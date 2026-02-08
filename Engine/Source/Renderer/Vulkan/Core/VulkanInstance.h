#pragma once

#include "Renderer/Vulkan/VulkanIncludes.h"

class CVulkanInstance
{
public:
	CVulkanInstance();
	~CVulkanInstance();

	void Init();

	void Destroy();

	GE_INLINE VkInstance GetInstance() const { return m_instance; }

private:
	VkInstance m_instance;
#ifdef _DEBUG
	VkDebugUtilsMessengerEXT m_debugCallback;
#endif
};