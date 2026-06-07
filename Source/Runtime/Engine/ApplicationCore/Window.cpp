#include "Window.h"

IWindow::IWindow()
{
	mHandle = nullptr;
	mWindowProps = { };
}

IWindow::~IWindow()
{
	DestroyWindow();
}

bool IWindow::InitWindow(const WindowProperties& windowProps)
{
	int windowFlags = SDL_WINDOW_OPENGL;
	mHandle = SDL_CreateWindow(windowProps.title, windowProps.width, windowProps.height, windowFlags);
	if (mHandle == nullptr)
	{
		SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
		return false;
	}

	mWindowProps = windowProps;
	return true;
}

void IWindow::DestroyWindow()
{
	SDL_DestroyWindow(mHandle);
	mHandle = nullptr;
}	