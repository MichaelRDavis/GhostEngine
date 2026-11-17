#pragma once

#include "RDICore.h"

class RDI_API IRDI
{
public:
	IRDI(const SRenderViewport& viewport);
	virtual ~IRDI();

	virtual void Init();
	virtual void Render(F32 deltaTime);
	virtual void Destroy();

protected:
	SRenderViewport mViewport;
};