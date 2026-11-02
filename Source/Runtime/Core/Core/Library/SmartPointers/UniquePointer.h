#pragma once

#include "Core.h"

template<typename Type>
class TUniquePointer
{
public:
	TUniquePointer(Type* ptr = nullptr)
		: mPtr(ptr)
	{
		
	}

	~TUniquePointer()
	{
		if (mPtr != nullptr)
		{
			delete mPtr;
			mPtr = nullptr;
		}
	}

	Type& operator*() const
	{
		return *mPtr;
	}

	Type* operator->() const
	{
		return mPtr;
	}

	bool operator!() const
	{
		return mPtr == nullptr;
	}

	operator bool() const
	{
		return mPtr != nullptr;
	}

	void Swap(TUniquePointer& other)
	{
		Type* tempPtr = other.mPtr;
		other.mPtr = mPtr;
		mPtr = tempPtr;
	}

	void Reset(Type* ptr = nullptr)
	{
		assert(ptr == nullptr || ptr != mPtr);
		this(ptr).Swap(*this);
	}

	Type* Get() const
	{
		return mPtr;
	}
	
private:
	Type* mPtr;
};

template<typename Type>
TUniquePointer<Type> MakeUnique()
{
	return TUniquePointer<Type>(new Type());
}