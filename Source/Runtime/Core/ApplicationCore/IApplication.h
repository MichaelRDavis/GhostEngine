#pragma once

struct ApplicationInfo
{
	const char* appName;
	bool bIsWindowed;
};

class IApplication
{
public:
	IApplication(const ApplicationInfo& appInfo);
	~IApplication();

	virtual void Init();

	virtual void Run();

	virtual void Destroy();

protected:
	ApplicationInfo mAppInfo;
};