#pragma once

#include "Core.h"

template<typename Type, U32 Elements>
class TArray
{
public:
	TArray();
	~TArray();

	void Init(const Type& element);

	const Type& operator[](U32 index) const;
	Type& operator[](U32 index);

	const Type& At(U32 index) const;
	Type& At(U32 index);

	Type* Begin();
	const Type* Begin() const;
	Type* End();
	const Type* End() const;

	Type* GetData();
	const Type* GetData() const;

	U32 Size() const;
	U32 MaxSize() const;
	bool IsEmpty() const;

private:
	Type m_array[Elements];
};

template<typename Type, U32 Elements>
GE_INLINE TArray<Type, Elements>::TArray()
{

}

template<typename Type, U32 Elements>
GE_INLINE TArray<Type, Elements>::~TArray()
{
	
}

template<typename Type, U32 Elements>
GE_INLINE void TArray<Type, Elements>::Init(const Type& element)
{
	CMemory::Memset(m_array, element, Elements);
}

template<typename Type, U32 Elements>
GE_INLINE const Type& TArray<Type, Elements>::operator[](U32 index) const
{
	return m_array[index];
}

template<typename Type, U32 Elements>
GE_INLINE Type& TArray<Type, Elements>::operator[](U32 index)
{
	return m_array[index];
}

template<typename Type, U32 Elements>
GE_INLINE const Type& TArray<Type, Elements>::At(U32 index) const
{
	return m_array[index];
}

template<typename Type, U32 Elements>
GE_INLINE Type& TArray<Type, Elements>::At(U32 index)
{
	return m_array[index];
}

template<typename Type, U32 Elements>
GE_INLINE Type* TArray<Type, Elements>::Begin()
{
	return &m_array[0];
}

template<typename Type, U32 Elements>
GE_INLINE const Type* TArray<Type, Elements>::Begin() const
{
	return &m_array[0];
}

template<typename Type, U32 Elements>
GE_INLINE Type* TArray<Type, Elements>::End()
{
	return &m_array[Elements];
}

template<typename Type, U32 Elements>
GE_INLINE const Type* TArray<Type, Elements>::End() const
{
	return &m_array[Elements];
}

template<typename Type, U32 Elements>
GE_INLINE Type* TArray<Type, Elements>::GetData()
{
	return &m_array;
}

template<typename Type, U32 Elements>
GE_INLINE const Type* TArray<Type, Elements>::GetData() const
{
	return &m_array;
}

template<typename Type, U32 Elements>
GE_INLINE U32 TArray<Type, Elements>::Size() const
{
	return Elements;
}

template<typename Type, U32 Elements>
GE_INLINE U32 TArray<Type, Elements>::MaxSize() const
{
	return Elements;
}

template<typename Type, U32 Elements>
GE_INLINE bool TArray<Type, Elements>::IsEmpty() const
{
	return Elements == 0;
}