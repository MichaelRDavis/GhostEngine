#pragma once

#include "Platform/PlatformHeader.h"

struct FRenderSurface
{
	SDL_Window* surfaceWindow;
	I32 surfaceWidth;
	I32 surfaceHeight;
};

class IRenderer
{
public:
	IRenderer() {}
	virtual ~IRenderer() {}

	virtual void Init(const FRenderSurface& surface) {}
	virtual void Render() {}
	virtual void Destroy() {}
};