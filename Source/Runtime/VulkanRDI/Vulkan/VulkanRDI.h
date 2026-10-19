#pragma once

#include "RDI/IRDI.h"

class VULKANRDI_API CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	virtual void Init();
	virtual void Render();
	virtual void Destroy();
};