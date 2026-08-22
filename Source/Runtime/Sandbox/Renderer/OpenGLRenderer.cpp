#include "OpenGLRenderer.h"
#ifdef GE_OPENGL_RENDERER
	#include <glad/glad.h>
#endif

COpenGLRenderer::COpenGLRenderer()
{
	mContext = nullptr;
	mRenderSurface = {};
}

COpenGLRenderer::~COpenGLRenderer()
{
	Destroy();
}

void COpenGLRenderer::Init(const FRenderSurface& surface)
{
	mRenderSurface = surface;

	mContext = SDL_GL_CreateContext(surface.surfaceWindow);
	if (mContext == nullptr)
	{
		printf("SDL OpenGL context creation failed! Error: %s\n", SDL_GetError());
		return;
	}

	SDL_GL_MakeCurrent(surface.surfaceWindow, mContext);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("glad failed to intialize!\n");
		return;
	}
}

void COpenGLRenderer::Render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	SDL_GL_SwapWindow(mRenderSurface.surfaceWindow);
}

void COpenGLRenderer::Destroy()
{
	SDL_GL_DestroyContext(mContext);
}