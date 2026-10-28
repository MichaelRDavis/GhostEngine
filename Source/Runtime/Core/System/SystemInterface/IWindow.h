#pragma once

#include "Core.h"

class IWindow
{
public:
	IWindow(IApplication* appOwner) {}
	virtual ~IWindow() {}

	virtual void Init() {}
	virtual void Destroy() {}

	virtual IApplication* GetApplicationOwner() const {return nullptr;}
	virtual void* GetWindowHandle() const {return nullptr;}
};