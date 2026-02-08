#pragma once

#include "Platform/Platform.h"

template<typename Type, typename Elements>
class TArray
{
public:
	TArray();
	~TArray();

	Type& operator[](U32 index);

	const Type& operator[](U32 index) const;

	Type* GetData();

	const Type* GetData() const;

	U32 Size() const;

private:
	Type m_array[Elements];
};

template<typename Type, typename Elements>
GE_INLINE TArray<Type, Elements>::TArray()
{

}

template<typename Type, typename Elements>
GE_INLINE TArray<Type, Elements>::~TArray()
{
	
}

template<typename Type, typename Elements>
GE_INLINE Type& TArray<Type, Elements>::operator[](U32 index)
{
	return m_array[index];
}

template<typename Type, typename Elements>
GE_INLINE const Type& TArray<Type, Elements>::operator[](U32 index) const
{
	return m_array[index];
}

template<typename Type, typename Elements>
inline Type* TArray<Type, Elements>::GetData()
{
	return &m_array;
}

template<typename Type, typename Elements>
inline const Type* TArray<Type, Elements>::GetData() const
{
	return &m_array;
}

template<typename Type, typename Elements>
inline U32 TArray<Type, Elements>::Size() const
{
	return Elements;
}
