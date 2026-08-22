#pragma once

#include "Platform/PlatformHeader.h"

struct FWindowDefinition
{
	const char* title;
	I32 width;
	I32 height;
};

class IApplication
{
public:
	IApplication();
	~IApplication();

	void AppInit(const FWindowDefinition& definition);
	void AppRun();
	void AppExit();

	GE_INLINE SDL_Window* GetWindow() const {return mWindow;}
	GE_INLINE bool IsAppRunning() const {return mIsAppRunning;}

private:
	SDL_Window* mWindow;
	bool mIsAppRunning;
};