#pragma once

#include "CoreExport.h"
#include "IWindow.h"

struct ApplicationInfo
{
	const char* appName;
	bool bIsWindowed;

	WindowInfo winInfo;
};

class CORE_API IApplication
{
public:
	IApplication(const ApplicationInfo& appInfo);
	~IApplication();

	virtual void Init();

	virtual void Run();

	virtual void Destroy();

	inline IWindow* GetWindow() const
	{
		return mWindow;
	}

protected:
	ApplicationInfo mAppInfo;

	IWindow* mWindow;
};