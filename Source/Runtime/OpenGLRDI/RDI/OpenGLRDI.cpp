#include "OpenGLRDI.h"
#include <glad/glad.h>
#include <cstdio>

COpenGLRDI::COpenGLRDI()
{
	mContext = nullptr;
}

COpenGLRDI::~COpenGLRDI()
{
	Destroy();
}

void COpenGLRDI::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		printf("glad OpenGL loader failed!\n");
		return;
	}
}

void COpenGLRDI::Render()
{
	Color color;
	color.r = 0.39f;
	color.g = 0.58f;
	color.b = 0.93f;
	color.a = 1.0f;

	ClearColor(color);
	Clear();

	SwapBuffers();
}

void COpenGLRDI::Destroy()
{
	if (mContext != nullptr)
	{
		SDL_GL_DestroyContext(mContext);
		mContext = nullptr;
	}
}

void COpenGLRDI::CreateViewport(const RenderViewport& viewport)
{
	mViewport = viewport;

	mContext = SDL_GL_CreateContext((SDL_Window*)mViewport.windowSurface);
	if (mContext == nullptr)
	{
		printf("SDL OpenGL context creation failed! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	SDL_GL_MakeCurrent((SDL_Window*)mViewport.windowSurface, mContext);
}

void COpenGLRDI::SwapBuffers()
{
	SDL_GL_SwapWindow((SDL_Window*)mViewport.windowSurface);
}

void COpenGLRDI::ClearColor(const Color& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void COpenGLRDI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}