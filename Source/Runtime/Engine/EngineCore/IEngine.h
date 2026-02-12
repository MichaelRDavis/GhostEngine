#pragma once

#include "EngineExport.h"
#include "Core.h"
#include "Logging/Assertions.h"

struct Viewport;
class IRDI;

class ENGINE_API IEngine
{
public:
	IEngine();
	~IEngine();

	void Init(const Viewport& viewport);

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

extern IEngine* gEngine;

extern IEngine* GetEngine();