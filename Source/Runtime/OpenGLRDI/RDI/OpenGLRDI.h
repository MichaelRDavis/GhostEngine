#pragma once

#include "IRDI.h"
#include <SDL3/SDL.h>

class OPENGLRDI_API COpenGLRDI : public IRDI
{
public:
	COpenGLRDI();
	~COpenGLRDI();

	virtual void Init();
	virtual void Render();
	virtual void Destroy();

	virtual void CreateViewport(const RenderViewport& viewport);

	virtual void SubmitVertexBuffer(VertexBuffer& buffer);

	virtual void SubmitIndexBuffer(IndexBuffer& buffer);

	virtual void SubmitVertexArray(VertexArray& vertexArray);

	virtual void SubmitVertexAttribute(VertexAttribute& vertexAttribute);

	virtual void SubmitShader(const char* vertexSrc, const char* fragSrc);

	virtual void SwapBuffers();
	virtual void ClearColor(const Color& color);
	virtual void Clear();

private:
	SDL_GLContext mContext;
};