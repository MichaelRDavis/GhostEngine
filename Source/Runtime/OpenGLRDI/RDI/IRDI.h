#pragma once

#include "OpenGLRDIExport.h"
#include <cstdint>

struct RenderViewport
{
	void* windowSurface;
	int32_t viewportWidth;
	int32_t viewportHeight;
};

struct Color
{
	float r;
	float g;
	float b;
	float a;
};

struct VertexBuffer
{
	uint32_t id;
	uint32_t vbo;
	uint64_t size;
	void* data;
};

struct VertexArray
{
	uint32_t id;
	uint32_t vao;
};

struct VertexAttribute
{
	uint32_t index;
	uint32_t size;
	uint64_t stride;
};

class OPENGLRDI_API IRDI
{
public:
	IRDI() {}
	virtual ~IRDI() {}

	virtual void Init() {}
	virtual void Render() {}
	virtual void Destroy() {}

	virtual void CreateViewport(const RenderViewport& viewport) {}

	virtual void SubmitVertexBuffer(VertexBuffer& buffer) {}

	virtual void SubmitVertexArray(VertexArray& vertexArray) {}

	virtual void SubmitVertexAttribute(VertexAttribute& vertexAttribute) {}

	virtual void SubmitShader(const char* vertexSrc, const char* fragSrc) {}

	virtual void SwapBuffers() {}
	virtual void ClearColor(const Color& color) {}
	virtual void Clear() {}

protected:
	RenderViewport mViewport = {};
};