#pragma once

#include "Core.h"

class IApplication;

enum class EWindowMode
{
	Fullscreen,
	WindowedBorderless,
	Windowed
};

struct FWindowDescription
{
	const char* title;
	EWindowMode windowMode;
	I32 positionX;
	I32 positionY;
	I32 width;
	I32 height;
	bool isHidden;
	bool isActive;
};

class CORE_API IWindow
{
public:
	IWindow(IApplication* appOwner, const FWindowDescription winDesc) {}
	virtual ~IWindow() {}

	virtual void Init() {}
	virtual void Destroy() {}

	GHOST_INLINE virtual void* GetWindowHandle() const {return nullptr;}
};