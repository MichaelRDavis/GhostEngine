#pragma once

#include "Core.h"

struct FWindowDescription;
class IWindow;

class CORE_API IApplication
{
public:
	IApplication() {}
	~IApplication() {}

	static IWindow* InitWindow(const FWindowDescription& winDesc) {return nullptr;}

	virtual void Init() {}
	virtual void Run() {}
	virtual void Destroy() {}

	GHOST_INLINE static IWindow* GetWindow() {return nullptr;}
};