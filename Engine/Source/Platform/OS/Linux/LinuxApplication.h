#pragma once

#include "Platform/OS/Interface/IApplication.h"

#ifdef GE_LINUX_PLATFORM
class CLinuxApplication : public IApplication
{
public:
	CLinuxApplication();
	~CLinuxApplication();

	void Init();

	void InitWindow(const WindowDescription& description);

	void HandleMessages();

	void Destroy();

private:
	SDL_Window* m_windowHandle;
	WindowDescription m_description;
};
#endif