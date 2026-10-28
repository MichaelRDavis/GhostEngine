#pragma once

template<typename Type>
class TSharedPointer
{
public:
	TSharedPointer()
	{
		mPtr = nullptr;
	}

	TSharedPointer(Type* ptr = nullptr)
		: mPtr(ptr)
	{
		
	}

	Type* Get() const
	{
		return mPtr;
	}

private:
	Type* mPtr;
};