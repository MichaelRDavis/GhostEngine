#pragma once

#ifdef CORE_EXPORT
	#define CORE_API __declspec(dllexport)
#else
	#define CORE_API __declspec(dllimport)
#endif

struct ApplicationInfo
{
	const char* appName;
	int windowPosX;
	int windowPosY;
	int windowWidth;
	int windowHeight;
	bool isWindowed;
	bool hasConsole;
	bool centerWindow;

	ApplicationInfo()
	{
		appName = "\0";
		windowPosX = 0;
		windowPosY = 0;
		windowWidth = 0;
		windowHeight = 0;
		isWindowed = false;
		hasConsole = false;
		centerWindow = false;
	}
};

class CORE_API IApplication
{
public:
	IApplication() {}
	virtual ~IApplication() {}

	virtual bool AppInit(const ApplicationInfo& appInfo) { return true; }
	virtual void AppRun() {}
	virtual void AppExit() {}

	inline bool IsAppRunning() const
	{
		return mIsAppRunning;
	}

protected:
	bool mIsAppRunning = false;
};