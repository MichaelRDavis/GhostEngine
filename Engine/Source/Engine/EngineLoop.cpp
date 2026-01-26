#include "EngineLoop.h"
#include "Platform/Timer/Timer.h"
#include "Core/Core.h"
#include "GObject.h"
#ifdef GE_WINDOWS_PLATFORM
#include "Platform/Windows/WindowsApplication.h"
#endif

CEngineLoop::CEngineLoop(CWindowsApplication& app)
	: m_application(app)
{
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

	CGObject* testObject = new CGObject();

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

	WindowDescription winDesc;
	m_application.InitWindow(winDesc);

	m_isInitialised = true;
	m_isRunning = true;

	delete testObject;
}

void CEngineLoop::Run()
{
//#ifdef _DEBUG
//	GE_LOG(Log, CMemoryTracker::GetMemoryUsage());
//#endif

	while (m_isRunning)
	{
		m_application.HandleMessages();
	}
}

void CEngineLoop::Exit()
{
	CMemoryTracker::Destroy();
	CLog::Destroy();
}