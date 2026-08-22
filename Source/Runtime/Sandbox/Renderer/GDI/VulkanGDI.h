#pragma once

#include "IGDI.h"

#ifdef GE_VULKAN_RENDERER
class CVulkanGDI : public IGDI
{
public:
	CVulkanGDI();
	~CVulkanGDI();
};
#endif