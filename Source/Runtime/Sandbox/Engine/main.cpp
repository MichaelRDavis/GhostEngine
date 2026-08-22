#include "Platform/ApplicationCore/IApplication.h"

#if defined(GE_OPENGL_RENDERER)
	#include "Renderer/GDI/OpenGLGDI.h"
#elif defined(GE_VULKAN_RENDERER)
	#include "Renderer/GDI/VulkanGDI.h"
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

	std::unique_ptr<IGDI> graphicsDevice;
#if defined(GE_OPENGL_RENDERER)
	graphicsDevice = std::make_unique<COpenGLGDI>();
#elif defined(GE_VULKAN_RENDERER)
	graphicsDevice = std::make_unique<CVulkanGDI>();
#endif
	graphicsDevice->Init(surface);

	FMesh triangle;
	triangle.vertices.push_back(FVec3(-0.5f, -0.5f, 0.0f));
	triangle.vertices.push_back(FVec3(0.5f, -0.5f, 0.0f));
	triangle.vertices.push_back(FVec3(0.0f, 0.5f, 0.0f));

	graphicsDevice->SubmitMesh(triangle);

	while (app.IsAppRunning())
	{
		app.AppRun();
		graphicsDevice->Render();
	}

	return 0;
}