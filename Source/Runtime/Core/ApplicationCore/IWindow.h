#pragma once

#include <cstdint>
#include <SDL3/SDL.h>

struct WindowInfo
{
	const char* title;
	int32_t posX;
	int32_t posY;
	int32_t width;
	int32_t height;
	bool bIsCentered;
};

class IWindow
{
public:
	IWindow(const WindowInfo& winInfo);
	~IWindow();

	virtual void Init();

	virtual void Destroy();

	inline SDL_Window* GetWindowHandle() const
	{
		return mWindowHandle;
	}

protected:
	WindowInfo mWinInfo;
	SDL_Window* mWindowHandle;
};