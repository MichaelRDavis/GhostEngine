#pragma once

#include "RDIExport.h"
#include "Core.h"

struct Viewport
{
	I32 width;
	I32 height;
	void* viewportHandle;
};

class RDI_API IRDI
{
public:
	IRDI () {}
	~IRDI() {}

	virtual void Init(const Viewport& viewport) {}

	virtual void Render(F32 deltaTime) {}

	virtual void Destroy() {}
};