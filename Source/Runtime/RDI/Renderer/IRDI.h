#pragma once

#include "RendererCore/IViewport.h"

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

	virtual bool Init(const ViewportInfo& viewport) { return true; }
	virtual void Render() {}
	virtual void Destroy() {}

	inline IViewport* GetViewport() const
	{
		return mViewport;
	}

protected:
	IViewport* mViewport = nullptr;
};