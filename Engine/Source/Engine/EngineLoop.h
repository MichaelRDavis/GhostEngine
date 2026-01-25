#pragma once

#include "Platform/Platform.h"

#ifdef GE_WINDOWS_PLATFORM
class CWindowsApplication;
#endif

class CEngineLoop
{
public:
	CEngineLoop(CWindowsApplication& app);
	~CEngineLoop();

	void Init();

	void Run();

	void Exit();

private:
	CWindowsApplication& m_application;

	F64 m_lastTime;

	bool m_isInitialised;
	bool m_isRunning;
	bool m_isSuspended;
};