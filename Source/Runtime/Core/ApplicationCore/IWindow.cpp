#include "IWindow.h"
#include <cstdio>

IWindow::IWindow(const WindowInfo& winInfo)
	: mWinInfo(winInfo)
{
	mWindowHandle = nullptr;
}

IWindow::~IWindow()
{
	Destroy();
}

void IWindow::Init()
{
	uint32_t subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_WasInit(subsystemFlags))
	{
		printf("SDL is not initialised! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	int32_t winPosX = 0;
	int32_t winPosY = 0;

	if (mWinInfo.bIsCentered)
	{
		winPosX = SDL_WINDOWPOS_CENTERED;
		winPosY = SDL_WINDOWPOS_CENTERED;
	}
	else
	{
		winPosX = mWinInfo.posX;
		winPosY = mWinInfo.posY;
	}

	uint32_t windowFlags = SDL_WINDOW_OPENGL;
	SDL_Window* window = SDL_CreateWindow(
		mWinInfo.title,
		mWinInfo.width,
		mWinInfo.height,
		windowFlags);
	if (window == nullptr)
	{
		printf("SDL window creation failed! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	mWindowHandle = window;
	SDL_ShowWindow(mWindowHandle);
}

void IWindow::Destroy()
{
	if (mWindowHandle != nullptr)
	{
		SDL_DestroyWindow(mWindowHandle);
		mWindowHandle = nullptr;
	}
}