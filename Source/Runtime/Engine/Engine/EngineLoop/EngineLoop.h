#pragma once

#include "Engine.h"

class IApplication;
class IEngine;

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

	bool mIsEngineRunning;
};

extern IEngine* gEngine;

extern IEngine* GetEngine();