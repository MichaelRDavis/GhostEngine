#include "EngineLoop.h"
#include "Platform/Timer/ITimer.h"
#include "Platform/OS/Interface/IPlatform.h"
#include "Core/Core.h"
#include "Engine/Engine.h"
#include "Renderer/RDI.h"
#ifdef GE_WINDOWS_PLATFORM
#include "Platform/OS/Windows/WindowsApplication.h"
#endif

CEngineLoop::CEngineLoop()
{
	m_application = nullptr;
	m_lastTime = 0.0f;
	m_isInitialised = false;
	m_isRunning = false;
	m_isSuspended = false;
}

CEngineLoop::~CEngineLoop()
{
	Exit();
}

void CEngineLoop::Init()
{
	PlatformInfo info = IPlatform::GetPlatformInfo();

	ITimer::StartTimer();

	CLog::Init();
	CMemoryTracker::Init();

	GE_LOG(Log, "CPU Clock Speed: %d MHz", info.cpuClockSpeed);
	GE_LOG(Log, "CPU Cores: %d", info.cpuCores);
	GE_LOG(Log, "System Physical Memory: %d", info.memory);

	WindowDescription winDesc;
#ifdef GE_WINDOWS_PLATFORM
	m_application = new CWindowsApplication();
#endif
	m_application->Init();
	m_application->InitWindow(winDesc);

	Viewport viewport;
	viewport.width = m_application->GetWindowWidth();
	viewport.height = m_application->GetWindowHeight();
	viewport.viewportHandle = m_application->GetWindowHandle();

	gEngine = new CEngine();
	gEngine->Init(viewport);

	m_isInitialised = true;
	m_isRunning = true;
}

void CEngineLoop::Run()
{
#ifdef _DEBUG
	GE_LOG(Log, CMemoryTracker::GetMemoryUsage());
#endif

	while (m_isRunning)
	{
		gEngine->Update(0.0f);

		m_application->HandleMessages();
	}
}

void CEngineLoop::Exit()
{
	if (gEngine != nullptr)
	{
		gEngine->Destroy();
		delete gEngine;
		gEngine = nullptr;
	}

	if (m_application != nullptr)
	{
		m_application->Destroy();
		delete m_application;
		m_application = nullptr;
	}

	CMemoryTracker::Destroy();
	CLog::Destroy();
}