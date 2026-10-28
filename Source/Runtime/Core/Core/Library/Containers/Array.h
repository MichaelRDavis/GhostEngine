#pragma once

#include "Core.h"

template<typename Type, U64 Elements>
class TArray
{
public:
	TArray()
	{
		CMemory::Zero(mArray, sizeof(mArray));
	}

	TArray(I32 value)
	{
		CMemory::Set(mArray, value, sizeof(mArray));
	}

	~TArray()
	{
		
	}

	const Type& operator[](I32 index) const
	{
		assert(index < Elements);
		return mArray[index];
	}

	Type& operator[](I32 index)
	{
		assert(index < Elements);
		return mArray[index];
	}

	const Type& At(I32 index) const
	{
		assert(index < Elements);
		return mArray[index];
	}

	Type& At(I32 index)
	{
		assert(index < Elements);
		return mArray[index];
	}

	void Add(const Type& element, I32 index)
	{
		assert(index < Elements);
		mArray[index] = element;
	}

	const Type& Remove(I32 index)
	{
		assert(index < Elements);
		Type element = mArray[index];
		mArray[index] = 0;
		return element;
	}

	void Zero()
	{
		CMemory::Zero(mArray, sizeof(mArray));
	}

	void Set(I32 value)
	{
		CMemory::Set(mArray, value, sizeof(mArray));
	}

	const Type* Get() const
	{
		return mArray;
	}

	Type* Get()
	{
		return mArray;
	}

	U64 Num() const
	{
		return Elements;
	}

	U64 NumBytes() const
	{
		return sizeof(mArray);
	}

private:
	Type mArray[Elements];
};