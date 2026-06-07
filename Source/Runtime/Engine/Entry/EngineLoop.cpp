#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "ApplicationCore/Window.h"

SDL_GLContext context = nullptr;
bool isRunning = false;

int main()
{
	int subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return -1;
	}

	WindowProperties winProps;
	winProps.title = "Engine";
	winProps.width = 1920;
	winProps.height = 1080;

	IWindow* window = new IWindow();
	if (!window->InitWindow(winProps))
	{
		return -1;
	}

	context = SDL_GL_CreateContext(window->GetHandle());
	if (context == nullptr)
	{
		SDL_Log("GL context could not be created! SDL error: %s\n", SDL_GetError());
		return -1;
	}

	SDL_GL_MakeCurrent(window->GetHandle(), context);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		SDL_Log("glad could not load OpenGL! SDL error: %s\n", SDL_GetError());
		return -1;
	}

	isRunning = true;

	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				isRunning = false;

				window->DestroyWindow();
				SDL_Quit();
			}
		}

		glClearColor(0.3f, 0.7f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		SDL_GL_SwapWindow(window->GetHandle());
	}

	return 0;
}