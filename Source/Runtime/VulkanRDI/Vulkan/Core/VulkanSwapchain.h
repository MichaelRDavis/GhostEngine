#pragma once

#include "Vulkan/VulkanIncludes.h"

class CVulkanSwapchain
{
public:
	CVulkanSwapchain();
	~CVulkanSwapchain();

	void Init();

	void Destroy();
};