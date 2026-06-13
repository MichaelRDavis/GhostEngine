#pragma once

#include "EngineExport.h"

class ENGINE_API IEngine
{
public:
	IEngine();
	~IEngine();

	virtual void Init();

	virtual void Update();

	virtual void Destroy();
};