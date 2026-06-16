#pragma once

#include "Renderer/IRDI.h"

#ifdef VULKANRDI_EXPORT
	#define VULKAN_API __declspec(dllexport)
#else
	#define VULKAN_API __declspec(dllimport)
#endif

class VULKAN_API CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	virtual bool Init(const RenderViewport& viewport);
	virtual void Render();
	virtual void Destroy();
};