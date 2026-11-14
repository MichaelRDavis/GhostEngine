#pragma once

#include "Engine.h"

class IEntity;

class ENGINE_API IComponent
{
public:
	IComponent();
	virtual ~IComponent();

protected:
	IEntity* mEntityOwner;
};