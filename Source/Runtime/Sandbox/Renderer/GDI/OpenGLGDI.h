#pragma once

#include "IGDI.h"

#ifdef GE_OPENGL_RENDERER
class COpenGLGDI : public IGDI
{
public:
	COpenGLGDI();
	~COpenGLGDI();

	void Init(const FRenderSurface& surface);
	void Render();
	void Destroy();

	void SubmitMesh(const FMesh& mesh);

private:
	SDL_GLContext mContext;
	FRenderSurface mRenderSurface;
};
#endif