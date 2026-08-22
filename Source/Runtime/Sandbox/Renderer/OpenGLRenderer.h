#pragma once

#include "IRenderer.h"

class COpenGLRenderer : public IRenderer
{
public:
	COpenGLRenderer();
	~COpenGLRenderer();

	void Init(const FRenderSurface& surface);
	void Render();
	void Destroy();

private:
	SDL_GLContext mContext;
	FRenderSurface mRenderSurface;
};