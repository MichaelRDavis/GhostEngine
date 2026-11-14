#pragma once

#include "Engine.h"

class IComponent;

class ENGINE_API IEntity
{
public:
	IEntity();
	virtual ~IEntity();

	GHOST_FORCEINLINE U64 GetEntityID() const { return mEntityID; }

protected:
	U64 mEntityID;
	std::map<U64, IComponent*> mComponentList;
};