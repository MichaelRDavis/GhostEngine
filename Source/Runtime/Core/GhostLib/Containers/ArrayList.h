#pragma once

#include "Core.h"

template<typename Type>
class TArrayList
{
public:
	TArrayList();
	~TArrayList();

	Type& operator[](U32 index);
	
	const Type& operator[](U32 index) const;

	void Init(const Type& element, U32 size);

	void Resize(U32 newCapacity);

	void Clear();

	Type* GetData();

	const Type* GetData() const;

	U32 Size() const;

	U32 Capacity() const;

	bool IsEmpty() const;

private:
	void* AllocateArray(U32 capacity);

	void* ResizeArray(void* oldArray, U32 oldCapacity, U32 newCapacity);

	void FreeArray(void* array, U32 capacity);

private:
	Type* m_pArray;
	U32 m_size;
	U32 m_capacity;
};

template<typename Type>
GE_INLINE TArrayList<Type>::TArrayList()
{
	m_pArray = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template<typename Type>
GE_INLINE TArrayList<Type>::~TArrayList()
{
	Clear();
}

template<typename Type>
GE_INLINE Type& TArrayList<Type>::operator[](U32 index)
{
	return m_pArray[index];
}

template<typename Type>
GE_INLINE const Type& TArrayList<Type>::operator[](U32 index) const
{
	return m_pArray[index];
}

template<typename Type>
GE_INLINE void TArrayList<Type>::Init(const Type& element, U32 capacity)
{
	U32 newCapacity = capacity;
	if (newCapacity > m_capacity)
	{
		m_size = m_capacity;
		Resize(newCapacity);

		for (U32 i = 0; i < newCapacity; i++)
		{
			m_pArray[i] = element;
		}
	}

	m_size = newCapacity;
}

template<typename Type>
GE_INLINE void TArrayList<Type>::Resize(U32 newCapacity)
{
	//GE_ASSERT(newCapacity <= 0);

	if (newCapacity <= 0)
	{
		Clear();
		return;
	}

	m_pArray = (Type*)ResizeArray(m_pArray, m_capacity, newCapacity);
	m_capacity = newCapacity;
	if (m_capacity < m_size)
	{
		m_size = m_capacity;
	}
}

template<typename Type>
GE_INLINE void TArrayList<Type>::Clear()
{
	if (m_pArray)
	{
		FreeArray(m_pArray, m_capacity);
	}

	m_pArray = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template<typename Type>
GE_INLINE Type* TArrayList<Type>::GetData()
{
	return m_pArray;
}

template<typename Type>
GE_INLINE const Type* TArrayList<Type>::GetData() const
{
	return m_pArray;
}

template<typename Type>
GE_INLINE U32 TArrayList<Type>::Size() const
{
	return m_size;
}

template<typename Type>
GE_INLINE U32 TArrayList<Type>::Capacity() const
{
	return m_capacity;
}

template<typename Type>
GE_INLINE bool TArrayList<Type>::IsEmpty() const
{
	return m_size == 0;
}

template<typename Type>
GE_INLINE void* TArrayList<Type>::AllocateArray(U32 capacity)
{
	Type* newArray = nullptr;
	newArray = (Type*)CMemory::Malloc(sizeof(Type) * capacity, MEM_TAG_ArrayList);

	for (U32 i = 0; i < capacity; i++)
	{
		new (&newArray[i])Type();
	}

	return newArray;
}

template<typename Type>
GE_INLINE void* TArrayList<Type>::ResizeArray(void* array, U32 oldCapacity, U32 newCapacity)
{
	Type* oldArray = (Type*)array;
	Type* newArray = nullptr;
	if (newCapacity > 0)
	{
		newArray = (Type*)AllocateArray(newCapacity);
		U32 overlap = (newCapacity < oldCapacity) ? newCapacity : oldCapacity;
		for (U32 i = 0; i < overlap; i++)
		{
			newArray[i] = oldArray[i];
		}
	}

	FreeArray(array, oldCapacity);

	return newArray;
}

template<typename Type>
GE_INLINE void TArrayList<Type>::FreeArray(void* array, U32 capacity)
{
	for (U32 i = 0; i < capacity; i++)
	{
		((Type*)array)[i].~Type();
	}

	CMemory::Free(array, MEM_TAG_ArrayList);
}