#pragma once

#include "Engine.h"

class ENGINE_API IEngine
{
public:
	IEngine();
	virtual ~IEngine();

	virtual void Init(const SRenderViewport& viewport);
	virtual void Update(F64 deltaTime);
	virtual void Destroy();

protected:
	IRDI* mRenderer;
};