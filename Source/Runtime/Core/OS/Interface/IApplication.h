#pragma once

#include "CoreExport.h"
#include "Core.h"

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

class CORE_API IApplication
{
public:
	IApplication() {}
	~IApplication() {}

	virtual void Init() {}

	virtual void InitWindow(const WindowDescription& description) {}

	virtual void HandleMessages() {}

	virtual void Destroy() {}

	GE_INLINE virtual void* GetWindowHandle() const { return nullptr; }

	GE_INLINE U32 GetWindowWidth() const { return m_windowWidth; }

	GE_INLINE U32 GetWindowHeight() const { return m_windowHeight; }

protected:
	U32 m_windowWidth;
	U32 m_windowHeight;
};