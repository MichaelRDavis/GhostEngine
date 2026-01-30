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

private:
	VkInstance m_instance;
};