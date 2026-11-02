#pragma once

#include "Core.h"

template<typename Key, typename Type>
class TNode
{
public:
	TNode()
	{
		
	}
	
private:
	Key mKey;
	Type mType;
	TNode<Key, Type>* mNextNode;
};

template<typename Key, typename Type>
class TMap
{
public:
	
private:
	TNode<Key, Type>** mMap;
	U64 mSize;
	U64 mElements;
};