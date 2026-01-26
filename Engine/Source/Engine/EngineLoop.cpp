#include "EngineLoop.h"
#include "Platform/Timer/Timer.h"
#include "Core/Core.h"
#ifdef GE_WINDOWS_PLATFORM
#include "Platform/Application/Windows/WindowsApplication.h"
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
	CLog::Init();
	CTimer::StartTimer();
	CMemoryTracker::Init();

	WindowDescription winDesc;
#ifdef GE_WINDOWS_PLATFORM
	m_application = new CWindowsApplication();
#endif
	m_application->Init();
	m_application->InitWindow(winDesc);

	TArrayList<U32> testArray;
	testArray.Init(10, 5);
	if (!testArray.IsEmpty())
	{
		U32 size = testArray.Size();
		U32 capacity = testArray.Capacity();

		for (U32 i = 0; i < testArray.Size(); i++)
		{
			GE_LOG(Log, "%d", testArray[i]);
		}
	}

	testArray.Clear();

	//GE_LOG(Fatal, "Hello, World!");
	GE_LOG(Error, "Hello, World!");
	GE_LOG(Warning, "Hello, World!");
	GE_LOG(Display, "Hello, World!");
	GE_LOG(Log, "Hello, World!");
	GE_LOG(Verbose, "Hello, World!");
	GE_LOG(VeryVerbose, "Hello, World!");

	//GE_CHECK(1 == 0);
	//GE_ASSERT(1 == 0);

	m_isInitialised = true;
	m_isRunning = true;
}

void CEngineLoop::Run()
{
//#ifdef _DEBUG
//	GE_LOG(Log, CMemoryTracker::GetMemoryUsage());
//#endif

	while (m_isRunning)
	{
		m_application->HandleMessages();
	}
}

void CEngineLoop::Exit()
{
	if (m_application != nullptr)
	{
		delete m_application;
		m_application = nullptr;
	}

	CMemoryTracker::Destroy();
	CLog::Destroy();
}