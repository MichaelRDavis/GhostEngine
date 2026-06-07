#include <SDL3/SDL.h>
#include <glad/glad.h>

#include <stdint.h>

struct Window
{
	const char* title;
	int width;
	int height;
	SDL_Window* handle;
} typedef Window;

int main()
{
	int32_t subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		return -1;
	}

	Window window;
	window.title = "Engine";
	window.width = 1920;
	window.height = 1080;

	int32_t windowFlags = SDL_WINDOW_OPENGL;
	window.handle = SDL_CreateWindow(window.title, window.width, window.height, windowFlags);
	if (window.handle == NULL)
	{
		return -1;
	}

	SDL_ShowWindow(window.handle);

	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				hasQuit = true;
				SDL_DestroyWindow(window.handle);
				SDL_Quit();
			}
		}
	}
}