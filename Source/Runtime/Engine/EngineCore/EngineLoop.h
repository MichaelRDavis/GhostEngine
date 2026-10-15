#pragma once

#include "EngineHeader.h"

class CEngine;

class ENGINE_API CEngineLoop
{
public:
	CEngineLoop();
	virtual ~CEngineLoop();

	virtual void InitializeEngine();

	virtual void RunEngine();

	virtual void DestroyEngine();
};

extern CEngine* gEngine = nullptr;

extern CEngine* GetEngine()
{
	if (gEngine)
	{
		return gEngine;
	}

	return nullptr;
}