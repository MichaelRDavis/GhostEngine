#include "Platform/IPlatform.h"
#include "ApplicationCore/IApplication.h"

int main()
{
	IPlatform::WriteToConsole("Hello, World!");

	ApplicationInfo appInfo;
	appInfo.appName = "Sandbox";
	appInfo.bIsWindowed = false;

	IApplication* app = IPlatform::CreateApplication(appInfo);

	return 0;
}