#include "IApplication.h"

IApplication::IApplication()
{
	mWindow = nullptr;
	mIsAppRunning = false;
}

IApplication::~IApplication()
{
	AppExit();
}

void IApplication::AppInit(const FWindowDefinition& definition)
{
	U32 subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		printf("SDL failed to initialize! Error: %s\n", SDL_GetError());
		return;
	}

	U32 windowFlags = 0;
#ifdef GE_OPENGL_RENDERER
	windowFlags = SDL_WINDOW_OPENGL;
#endif

	mWindow = SDL_CreateWindow(definition.title,definition.width, definition.height, windowFlags);
	if (mWindow == nullptr)
	{
		printf("SDL window creation failed! Error: %s\n", SDL_GetError());
		return;
	}

	mIsAppRunning = true;
}

void IApplication::AppRun()
{
	while (mIsAppRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
					AppExit();
					break;
			}
		}
	}
}

void IApplication::AppExit()
{
	mIsAppRunning = false;
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}