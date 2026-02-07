#pragma once

#include "Platform/Platform.h"

struct Viewport
{
	I32 width;
	I32 height;
	void* viewportHandle;
};

class IRDI
{
public:
	IRDI () {}
	~IRDI() {}

	virtual void Init(const Viewport& viewport) {}

	virtual void Render(F32 deltaTime) {}

	virtual void Destroy() {}
};