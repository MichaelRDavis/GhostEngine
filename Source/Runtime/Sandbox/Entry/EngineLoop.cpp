#include "Platform/IPlatform.h"
#include "ApplicationCore/IApplication.h"
#include "RDI/OpenGLRDI.h"

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

	RenderViewport viewport;
	viewport.windowSurface = app->GetWindow()->GetWindowHandle();
	viewport.viewportWidth = winInfo.width;
	viewport.viewportHeight = winInfo.height;

	IRDI* renderDevice = new COpenGLRDI();
	renderDevice->CreateViewport(viewport);
	renderDevice->Init();

	while (true)
	{
		app->Run();
		renderDevice->Render();
	}

	return 0;
}