#pragma once

#include "Core.h"

template<typename Type>
class TSharedPointer
{
public:
	TSharedPointer(Type* ptr = nullptr)
		: mPtr(ptr)
		, mCounter(new U64(0))
	{

	}

	~TSharedPointer()
	{
		mCounter--;
		if (mCounter == 0)
		{
			if (mPtr != nullptr)
			{
				delete mPtr;
				mPtr = nullptr;
			}

			delete mCounter;
			mCounter = nullptr;
		}
	}

	TSharedPointer(const TSharedPointer& other)
		: mPtr(other.mPtr)
		, mCounter(other.mCounter)
	{
		if (other.mPtr != nullptr)
		{
			mCounter++;
		}
	}

	TSharedPointer(TSharedPointer&& other)
	{
		mPtr = other.mPtr;
		mCounter = other.mCounter;
		other.mPtr = nullptr;
		other.mCounter = nullptr;
	}

	TSharedPointer& operator=(const TSharedPointer& other)
	{
		mPtr = other.mPtr;
		mCounter = other.mCounter;
		if (other.mPtr != nullptr)
		{
			mCounter++;
		}
	}

	TSharedPointer& operator=(TSharedPointer&& other)
	{
		mPtr = other.mPtr;
		mCounter = other.mCounter;
		other.mPtr = nullptr;
		other.mCounter = nullptr;
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

	void Swap(TSharedPointer& other)
	{
		Type* tempPtr = other.mPtr;
		U64* tempCounter = other.mCounter;
		other.mPtr = mPtr;
		other.mCounter = mCounter;
		mPtr = tempPtr;
		mCounter = tempCounter;
	}

	Type* Get() const
	{
		return mPtr;
	}

	U64 Count() const
	{
		return *mCounter;
	}

private:
	Type* mPtr;
	U64* mCounter;
};

template<typename Type>
TSharedPointer<Type> MakeShared()
{
	return TSharedPointer<Type>(new Type());
}