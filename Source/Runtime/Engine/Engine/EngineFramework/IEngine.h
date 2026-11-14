#pragma once

#include "Engine.h"

class ENGINE_API IEngine
{
public:
	IEngine() {}
	virtual ~IEngine() {}

	virtual void Init() {}
	virtual void Update(F32 deltaTime) {}
	virtual void Destroy() {}
};