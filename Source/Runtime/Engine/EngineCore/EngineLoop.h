#pragma once

#include "EngineHeader.h"

class IApplication;
class CEngine;

class ENGINE_API CEngineLoop
{
public:
	CEngineLoop();
	virtual ~CEngineLoop();

	virtual void Init();

	virtual void Run();

	virtual void Exit();

private:
	IApplication* mApp;
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