#pragma once

#include "Engine.h"

class IApplication;

class ENGINE_API CEngineLoop
{
public:
	CEngineLoop();
	~CEngineLoop();

	void EngineInit();
	void EngineUpdate();
	void EngineExit();

private:
	IApplication* mEngineApp;
};