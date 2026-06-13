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

class OPENGLRDI_API IRDI
{
public:
	IRDI() {}
	virtual ~IRDI() {}

	virtual void Init() {}
	virtual void Render() {}
	virtual void Destroy() {}

	virtual void CreateViewport(const RenderViewport& viewport) {}

	virtual void SwapBuffers() {}
	virtual void ClearColor(const Color& color) {}
	virtual void Clear() {}

protected:
	RenderViewport mViewport = {};
};