#pragma once

#include "Platform/Platform.h"

enum class EWindowMode
{
	Fullscreen,
	Windowed
};

struct WindowDescription
{
	const wchar_t* title;
	I32 width;
	I32 height;
	I32 posX;
	I32 posY;
	EWindowMode windowMode;
	bool isHidden;

	WindowDescription()
	{
		title = L"\0";
		width = 1920;
		height = 1080;
		posX = 0;
		posY = 0;
		windowMode = EWindowMode::Fullscreen;
		isHidden = false;
	}
};

class IApplication
{
public:
	IApplication() {}
	~IApplication() {}

	virtual void Init() {}

	virtual void InitWindow(const WindowDescription& description) {}

	virtual void HandleMessages() {}

	virtual void Destroy() {}
};