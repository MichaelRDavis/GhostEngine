#pragma once

#include "Renderer/RDI.h"

class CVulkanRDI : public IRDI
{
public:
	CVulkanRDI();
	~CVulkanRDI();

	void Init();

	void Render();

	void Destroy();
};