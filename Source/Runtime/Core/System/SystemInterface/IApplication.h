#pragma once

#include "Core.h"

enum class EWindowMode
{
	Fullscreen,
	WindowedFullscreen,
	Windowed
};

struct FWindowDescription
{
	const char* title;
	EWindowMode mode;
	U32 positionX;
	U32 positionY;
	U32 width;
	U32 height;
	bool isHidden;
	bool isActive;
};

class IWindow;

class CORE_API IApplication
{
public:
	IApplication(const FWindowDescription& winDesc) {}
	virtual ~IApplication() {}

	static IWindow* InitWindow() {return nullptr;}

	virtual void Init() {}
	virtual void Run() {}
	virtual void Exit() {}
};