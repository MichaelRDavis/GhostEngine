#pragma once

#include "EngineHeader.h"

class CEngine
{
public:
	CEngine();
	virtual ~CEngine();

	virtual void Initialize();
	virtual void Update();
	virtual void Destroy();
};