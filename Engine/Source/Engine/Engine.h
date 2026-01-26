#pragma once

#include "Platform/Platform.h"

class CEngine
{
public:
	CEngine();
	~CEngine();

	void Init();

	void Update(F32 deltaTime);

	void Destroy();
};