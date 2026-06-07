#include "OS/System.h"
#include "Renderer/Renderer.h"

int main()
{
	if (Sys_Init() != 0)
	{
		return -1;
	}

	Window window;
	window.title = "Engine";
	window.width = 1920;
	window.height = 1080;
	window.handle = 0;

	App app;
	app.bHasQuit = 0;
	app.window = window;

	if (Sys_CreateWindow(&app.window) != 0)
	{
		return -1;
	}

	RendererInfo info;
	info.context = 0;
	Renderer_CreateContext(&app.window, &info);

	while (!app.bHasQuit)
	{
		Sys_Run(&app);
		Renderer_Clear();
		Renderer_SwapBuffers(&app.window);
	}

	return 0;
}
