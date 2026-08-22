#pragma once

#include "Platform/PlatformHeader.h"
#include "Renderer/RenderCore/RendererTypes.h"

struct FRenderSurface
{
	SDL_Window* surfaceWindow;
	I32 surfaceWidth;
	I32 surfaceHeight;
};

class IGDI
{
public:
	IGDI() {}
	virtual ~IGDI() {}

	virtual void Init(const FRenderSurface& surface) {}
	virtual void Render() {}
	virtual void Destroy() {}

	virtual void SubmitMesh(const FMesh& mesh) {}
};