#pragma once

#include "Platform/Platform.h"
#include "Core/Logging/Assertions.h"

class IRDI;

class CEngine
{
public:
	CEngine();
	~CEngine();

	void Init();

	void Update(F32 deltaTime);

	void Destroy();

	GE_INLINE IRDI* GetRenderer() const
	{
		GE_CHECK(m_renderer);
		return m_renderer;
	}

private:
	IRDI* m_renderer;
};

extern CEngine* gEngine;

extern CEngine* GetEngine();