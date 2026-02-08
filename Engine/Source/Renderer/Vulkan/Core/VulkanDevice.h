#pragma once

#include "Renderer/Vulkan/VulkanIncludes.h"
#include "Platform/Platform.h"

class CVulkanInstance;

class CVulkanDevice
{
public:
	CVulkanDevice(CVulkanInstance& instance);
	~CVulkanDevice();

	void Init(VkSurfaceKHR surface);

	void Destroy();

	GE_INLINE VkPhysicalDevice GetGPU() const { return m_gpu; }

	GE_INLINE VkDevice GetDevice() const { return m_device; }

private:
	CVulkanInstance& m_instance;

	VkPhysicalDevice m_gpu;

	VkDevice m_device;

	I32 m_graphicsQueueIndex;
};