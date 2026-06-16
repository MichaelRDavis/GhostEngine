#pragma once

#include "RendererCore/RendererTypes.h"

#ifdef RDI_EXPORT
	#define RDI_API __declspec(dllexport)
#else
	#define RDI_API __declspec(dllimport)
#endif

class RDI_API IRDI
{
public:
	IRDI() {}
	virtual ~IRDI() {}

	virtual bool Init(const RenderViewport& viewport) { return true; }
	virtual void Render() {}
	virtual void Destroy() {}

protected:
	RenderViewport mRenderViewport = {};
};