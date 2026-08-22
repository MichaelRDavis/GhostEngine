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

	void CreateVertexArray();

	void CreateVertexBuffer(U32 size, void* data, EBufferUsage usage);

	void CreateIndexBuffer(U32 size, void* data, EBufferUsage usage);

	void AddVertexAttribute(U32 index, U32 size, U32 stride, U32 offset);

private:
	SDL_GLContext mContext;
	FRenderSurface mRenderSurface;
};
#endif