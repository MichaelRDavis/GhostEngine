#pragma once

#include <SDL3/SDL.h>

struct WindowProperties
{
	const char* title;
	int width;
	int height;
};

class IWindow
{
public:
	IWindow();
	~IWindow();

	bool InitWindow(const WindowProperties& windowProps);

	void DestroyWindow();

	inline SDL_Window* GetHandle() const
	{
		if (mHandle)
		{
			return mHandle;
		}

		return nullptr;
	}

private:
	SDL_Window* mHandle;

	WindowProperties mWindowProps;
};