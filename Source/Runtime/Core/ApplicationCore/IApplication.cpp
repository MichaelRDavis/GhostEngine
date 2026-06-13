#include "IApplication.h"
#include <SDL3/SDL.h>
#include <cstdio>

IApplication::IApplication(const ApplicationInfo& appInfo)
	: mAppInfo(appInfo)
{
	mWindow = nullptr;
}

IApplication::~IApplication() 
{
	Destroy();
}

void IApplication::Init()
{
	uint32_t subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		printf("SDL initialisation failed! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	if (mAppInfo.bIsWindowed)
	{
		mWindow = new IWindow(mAppInfo.winInfo);
		mWindow->Init();
	}
}

void IApplication::Run()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				Destroy();
				break;
		}
	}
}

void IApplication::Destroy()
{
	if (mWindow != nullptr)
	{
		mWindow->Destroy();
		delete mWindow;
		mWindow = nullptr;
	}

	SDL_Quit();
}