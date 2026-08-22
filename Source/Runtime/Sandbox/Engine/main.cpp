#include "Platform/ApplicationCore/IApplication.h"

int main()
{
	FWindowDefinition window;
	window.title = "Sandbox";
	window.height = 1080;
	window.width = 1920;

	IApplication app;
	app.AppInit(window);
	app.AppRun();

	return 0;
}