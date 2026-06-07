#include "Renderer.h"
#include "OS/System.h"
#include <glad/glad.h>
#include <SDL3/SDL.h>

int Renderer_CreateContext(Window* window, RendererInfo* info)
{
	info->context = SDL_GL_CreateContext(window->handle);
	SDL_GL_MakeCurrent(window->handle, info->context);
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	return 0;
}

void Renderer_Clear()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer_SwapBuffers(Window* window)
{
	SDL_GL_SwapWindow(window->handle);
}
