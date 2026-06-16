#pragma once

#include "Renderer/IRDI.h"

#ifdef OPENGLRDI_EXPORT
	#define OPENGLRDI_API __declspec(dllexport)
#else
	#define OPENGLRDI_API __declspec(dllimport)
#endif

class OPENGLRDI_API COpenGLRDI : public IRDI
{
public:
	COpenGLRDI();
	~COpenGLRDI();

	virtual bool Init(const ViewportInfo& viewport);
	virtual void Render();
	virtual void Destroy();
};