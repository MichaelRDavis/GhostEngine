#pragma once

#include "EngineHeader.h"

class CEngine
{
public:
	CEngine();
	virtual ~CEngine();

	virtual void Init();
	virtual void Update();
	virtual void Destroy();
};