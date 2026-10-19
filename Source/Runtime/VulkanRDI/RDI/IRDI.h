#pragma once

#include "VulkanHeader.h"

class VULKANRDI_API IRDI
{
public:
	IRDI() {}
	virtual ~IRDI() {}

	virtual void Init() {}
	virtual void Render() {}
	virtual void Destroy() {}
};