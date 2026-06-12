#pragma once

#include "CoreExport.h"
#include "Core.h"

typedef struct FWindowDefinition
{
	const char* title;
	int32 winPosX;
	int32 winPosY;
	int32 winWidth;
	int32 winHeight;

} FWindowDefinition;

typedef struct FApplication
{
	void* application;
	FWindowDefinition* winDefinition;

} FApplication;

CORE_API bool32 App_Init(FApplication* app, FWindowDefinition* winDef);
CORE_API void App_Run(FApplication* app);
CORE_API void App_Exit(FApplication* app);

bool32 App_HandleMessages(FApplication* app);