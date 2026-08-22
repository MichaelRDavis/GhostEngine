#include "Platform/ApplicationCore/IApplication.h"

#ifdef GE_OPENGL_RENDERER
	#include "Renderer/OpenGLRenderer.h"
#endif

int main()
{
	FWindowDefinition window;
	window.title = "Sandbox";
	window.height = 1080;
	window.width = 1920;

	IApplication app;
	app.AppInit(window);

	FRenderSurface surface;
	surface.surfaceWindow = app.GetWindow();
	surface.surfaceHeight = window.height;
	surface.surfaceWidth = window.width;

	std::unique_ptr<IRenderer> renderer;
#ifdef GE_OPENGL_RENDERER
	renderer = std::make_unique<COpenGLRenderer>();
#endif
	renderer->Init(surface);

	while (app.IsAppRunning())
	{
		app.AppRun();
		renderer->Render();
	}

	return 0;
}