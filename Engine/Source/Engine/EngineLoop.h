#pragma once

#include "Platform/Platform.h"

class IApplication;

class CEngineLoop
{
public:
	CEngineLoop();
	~CEngineLoop();

	void Init();

	void Run();

	void Exit();

private:
	IApplication* m_application;

	F64 m_lastTime;

	bool m_isInitialised;
	bool m_isRunning;
	bool m_isSuspended;
};