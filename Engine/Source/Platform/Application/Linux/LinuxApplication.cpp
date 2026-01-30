#include "LinuxApplication.h"

#ifdef GE_LINUX_PLATFORM
CLinuxApplication::CLinuxApplication()
{
	m_windowHandle = nullptr;
	m_description = { };
}

CLinuxApplication::~CLinuxApplication()
{
	Destroy();
}

void CLinuxApplication::Init()
{
	U32 subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_Init(subsystemFlags))
	{
		printf("SDL initialisation failed\n");
		return;
	}
}

void CLinuxApplication::InitWindow(const WindowDescription& description)
{
	m_description = description;

	U32 subsystemFlags = SDL_INIT_VIDEO;
	if (!SDL_WasInit(subsystemFlags))
	{
		printf("SDL is not initialised failed\n");
		return;
	}

	U32 windowFlags = SDL_WINDOW_VULKAN;
	m_windowHandle = SDL_CreateWindow(
		"Sandbox",
		m_description.width,
		m_description.height,
		windowFlags);
	if (m_windowHandle == nullptr)
	{
		printf("SDL window creation failed\n");
		return;
	}

	SDL_ShowWindow(m_windowHandle);
}

void CLinuxApplication::HandleMessages()
{	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			Destroy();
			break;
		}
	}
}

void CLinuxApplication::Destroy()
{
	if (m_windowHandle != nullptr)
	{
		SDL_DestroyWindow(m_windowHandle);
		m_windowHandle = nullptr;
	}

	SDL_Quit();
}
#endif