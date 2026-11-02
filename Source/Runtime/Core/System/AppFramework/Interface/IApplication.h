#pragma once

#include "Core.h"

struct SWindowDescription;
class IWindow;

class CORE_API IApplication
{
public:
	IApplication() {}
	~IApplication() {}

	virtual void MakeWindow(const SWindowDescription& winDesc) {}

	virtual void Init() {}
	virtual void Run() {}
	virtual void Destroy() {}

	GHOST_INLINE static IWindow* GetWindow() {return nullptr;}
};