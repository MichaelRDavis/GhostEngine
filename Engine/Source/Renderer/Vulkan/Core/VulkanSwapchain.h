#pragma once

#include "Renderer/Vulkan/VulkanIncludes.h"

class CVulkanSwapchain
{
public:
	CVulkanSwapchain();
	~CVulkanSwapchain();

	void Init();

	void Destroy();
};