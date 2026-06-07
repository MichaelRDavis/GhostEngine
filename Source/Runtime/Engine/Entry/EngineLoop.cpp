#include <SDL3/SDL.h>
#include <glad/glad.h>

SDL_Window* window = nullptr;
bool isRunning = false;

int main()
{
	int subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Engine", 640, 480, 0);
	if (window == nullptr)
	{
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
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

				SDL_DestroyWindow(window);
				window = nullptr;

				SDL_Quit();
			}
		}
	}

	return 0;
}