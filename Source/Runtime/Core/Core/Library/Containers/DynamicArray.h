#pragma once

#include "Core.h"

template<typename Type>
class TDynamicArray
{
public:
	typedef Type* Iterator;
	typedef const Type* ConstIterator;

	TDynamicArray()
	{
		mSize = 0;
		mElements = 0;
		mArray = nullptr;
	}

	TDynamicArray(U64 size)
		: mSize(size)
	{
		Reserve(size);
	}

	TDynamicArray(const TDynamicArray& other)
	{
		mArray = nullptr;
		*this = other;
	}

	~TDynamicArray()
	{
		Empty();
	}

	TDynamicArray<Type>& operator=(const TDynamicArray<Type>& other)
	{
		Empty();

		mElements = other.mElements;
		mSize = other.mSize;

		if (mSize > 0)
		{
			mArray = Allocate(mSize);
			for (U64 i = 0; i < mElements; i++)
			{
				mArray[i] = other.mArray[i];
			}
		}

		return *this;
	}

	Type& operator[](U64 index)
	{
		assert(index >= 0);
		assert(index < mElements);

		return mArray[index];
	}

	const Type& operator[](U64 index) const
	{
		assert(index >= 0);
		assert(index < mElements);

		return mArray[index];
	}

	void Init(const Type& element, U64 size)
	{
		U64 newElements = size;

		if (size > mSize)
		{
			size += (size >> 1);
			mElements = size;
			Resize(size);

			for (U64 i = mElements; i < size; i++)
			{
				mArray[i] = element;
			}
		}

		mElements = newElements;
	}

	void Insert(const Type& element, U64 index)
	{
		if (!mArray)
		{
			Resize(mDefaultSize);
		}

		if (mElements == mSize)
		{
			U64 newSize = 0;
			newSize += mSize >> 1;
			Resize(newSize);
		}

		if (index < 0)
		{
			index = 0;
		}
		else if (index > mElements)
		{
			index = mElements;
		}

		for (U64 i = mElements; i > index; --i)
		{
			mArray[i] = mArray[i - 1];
		}

		mElements++;
		mArray[index] = element;
	}

	void Add(const Type& element)
	{
		Emplace(element);
	}

	void AddUnique(const Type& element)
	{
		if (!Contains(element))
		{
			Emplace(element);
		}
	}

	void Emplace(const Type& element)
	{
		if (!mArray)
		{
			Resize(mDefaultSize);
		}

		if (mElements == mSize)
		{
			U64 newSize = 0;
			Resize(newSize += (mSize >> 1));
		}

		mArray[mElements] = element;
		mElements++;
	}

	U64 Find(const Type& element)
	{
		for (U64 index = 0; index < mElements; i++)
		{
			if (mArray[i] == element)
			{
				return index;
			}
		}

		return -1;
	}

	bool Contains(const Type& element)
	{
		for (U64 index = 0; index < mElements; i++)
		{
			if (mArray[i] == element)
			{
				return true;
			}
		}

		return false;
	}

	void Empty()
	{
		if (mArray)
		{
			Free(mArray, mSize);
		}

		mArray = nullptr;
		mElements = 0;
		mSize = 0;
	}

	void SetNum(U64 newElements)
	{
		assert(newElements > 0);
		if (newElements > mSize)
		{
			Resize(newElements);
		}

		mElements = newElements;
	}

	void Shrink()
	{
		if (mArray)
		{
			if (mElements > 0)
			{
				Resize(mElements);
			}
			else
			{
				Empty();
			}
		}
	}

	void Resize(U64 newSize)
	{
		assert(newSize >= 0);

		if (newSize <= 0)
		{
			Empty();
			return;
		}

		if (newSize == mSize)
		{
			return;
		}

		mArray = Reallocate(mArray, mSize, newSize);
		mSize = newSize;

		if (mSize < mElements)
		{
			mElements = mSize;
		}
	}

	void Reserve(U64 newSize)
	{
		U64 newElements = newSize;

		if (newSize > mSize)
		{
			newSize += (newSize >> 1);
			Resize(newSize);
		}

		mElements = newElements;
	}

	U64 Num() const
	{
		return mElements;
	}

	U64 Size() const
	{
		return mSize;
	}

	U64 GetTypeSize() const
	{
		return mSize * sizeof(Type);
	}

	U64 NumBytes() const
	{
		return sizeof(TDynamicArray<Type>) + GetTypeSize();
	}

	bool IsEmpty() const
	{
		return mElements == 0;
	}

	Type* Get() 
	{
		return mArray;
	}

	const Type* Get() const
	{
		return mArray;
	}

private:
	Type* Allocate(U64 size)
	{
		Type* newArray = nullptr;
		newArray = (Type*)malloc(sizeof(Type) * size);

		for (U64 i = 0; i < size; i++)
		{
			new(&newArray[i])Type();
		}

		return newArray;
	}

	Type* Reallocate(Type* array, U64 oldSize, U64 newSize)
	{
		Type* oldArray = array;
		Type* newArray = nullptr;

		if (newSize > 0)
		{
			newArray = Allocate(newSize);
			U64 sizeDiff = CMath::Min<U64>(oldSize, newSize);
			for (U64 i = 0; i < sizeDiff; i++)
			{
				newArray[i] = oldArray[i];
			}
		}

		Free(array, oldSize);
		return newArray;
	}

	void Free(Type* array, U64 size)
	{
		for (U64 i = 0; i < size; i++)
		{
			array[i].~Type();
		}

		free(array);
	}

private:
	U64 mSize;
	U64 mDefaultSize = 16;
	U64 mElements;
	Type* mArray;
};