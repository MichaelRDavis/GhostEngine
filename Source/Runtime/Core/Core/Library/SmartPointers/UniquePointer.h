#pragma once

template<typename Type>
class TUniquePointer
{
public:
	TUniquePointer()
	{
		mPtr = nullptr;
	}

	TUniquePointer(Type* ptr = nullptr)
		: mPtr(ptr)
	{

	}

	TUniquePointer(const TUniquePointer&) = delete;
	TUniquePointer& operator=(const TUniquePointer&) = delete;

	~TUniquePointer()
	{
		if (mPtr != nullptr)
		{
			delete mPtr;
			mPtr = nullptr;
		}
	}

	operator bool() const
	{
		return mPtr != nullptr;
	}

	Type& operator*() const
	{
		return *mPtr;
	}

	Type operator->() const
	{
		return mPtr;
	}

	Type* Get() const
	{
		return mPtr;
	}

private:
	Type* mPtr;
};