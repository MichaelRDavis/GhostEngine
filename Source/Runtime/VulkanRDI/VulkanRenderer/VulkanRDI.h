#pragma once

#include "VulkanRDICore.h"

class VULKANRDI_API CVulkanRDI : public IRDI
{
public:
	CVulkanRDI(const SRenderViewport& viewport);
	~CVulkanRDI();

	void Init();
	void Render(F32 deltaTime);
	void Destroy();
};