#pragma once

#include "CoreHeader.h"

struct FWindowDefintion
{
	const char* title;
	I32 width;
	I32 height;
	I32 posX;
	I32 posY;

	FWindowDefintion()
	{
		title = "\0";
		width = 0;
		height = 0;
		posX = 0;
		posY = 0;
	}
};

class CORE_API IApplication
{
public:
	IApplication() {}
	virtual ~IApplication() {}

	virtual void Init(const FWindowDefintion& winDef) {}
	virtual void Exit() {}
	virtual void HandleMessages() {}
};