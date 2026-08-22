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

	virtual void CreateVertexArray() {}

	virtual void CreateVertexBuffer(U32 size, void* data, EBufferUsage usage) {}
	virtual void CreateIndexBuffer(U32 size, void* data, EBufferUsage usage) {}

	virtual void AddVertexAttribute(U32 index, U32 size, U32 stride, U32 offset) {}
};