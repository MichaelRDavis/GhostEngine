#include "Platform/IPlatform.h"
#include "ApplicationCore/IApplication.h"

int main()
{
	IPlatform::WriteToConsole("Hello, World!");

	ApplicationInfo appInfo;
	appInfo.appName = "Sandbox";
	appInfo.bIsWindowed = true;

	WindowInfo winInfo;
	winInfo.title = appInfo.appName;
	winInfo.width = 1920;
	winInfo.height = 1080;
	appInfo.winInfo = winInfo;

	IApplication* app = IPlatform::CreateApplication(appInfo);
	app->Init();

	while (true)
	{
		app->Run();
	}

	return 0;
}