#include "System.h"
#include <SDL3/SDL.h>

int Sys_Init()
{
	int32_t subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		return -1;
	}

	return 0;
}

void Sys_Quit()
{
	SDL_Quit();
}

int Sys_CreateWindow(Window* window)
{
	int32_t windowFlags = SDL_WINDOW_OPENGL;
	window->handle = SDL_CreateWindow(window->title, window->width, window->height, windowFlags);
	if (window->handle == NULL)
	{
		return -1;
	}

	SDL_ShowWindow(window->handle);

	return 0;
}

void Sys_DestroyWindow(Window* window)
{
	SDL_DestroyWindow(window->handle);
	window->handle = NULL;
}

void Sys_Run(App* app)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)
		{
			app->bHasQuit = true;

			Sys_DestroyWindow(&app->window);
			Sys_Quit();
		}
	}
}