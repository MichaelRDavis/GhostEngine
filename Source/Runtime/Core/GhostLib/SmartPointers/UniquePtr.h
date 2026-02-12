#pragma once

#include "Core.h"

template<typename Type>
class TUniquePtr
{
public:
	TUniquePtr();
	explicit TUniquePtr(Type* ptr);
	~TUniquePtr();

	TUniquePtr(const Type&) = delete;
	TUniquePtr& operator=(const Type&) = delete;
	TUniquePtr& operator=(Type*) = delete;

	Type& operator*() const;
	Type* operator->() const;

	explicit operator bool() const;

	void Reset();
	Type* Release();
	void Reset(Type* ptr = nullptr);
	void Swap(TUniquePtr& other);

	Type* Get() const;

private:
	Type* m_ptr;
};

template<typename Type>
GE_INLINE TUniquePtr<Type>::TUniquePtr()
	: m_ptr(nullptr)
{
	
}

template<typename Type>
GE_INLINE TUniquePtr<Type>::TUniquePtr(Type* ptr)
	: m_ptr(ptr)
{

}

template<typename Type>
GE_INLINE TUniquePtr<Type>::~TUniquePtr()
{
	if (m_ptr != nullptr)
	{
		delete m_ptr;
	}
}

template<typename Type>
GE_INLINE Type& TUniquePtr<Type>::operator*() const
{
	return *m_ptr;
}

template<typename Type>
GE_INLINE Type* TUniquePtr<Type>::operator->() const
{
	return m_ptr;
}

template<typename Type>
GE_INLINE TUniquePtr<Type>::operator bool() const
{
	return m_ptr != nullptr;
}

template<typename Type>
GE_INLINE void TUniquePtr<Type>::Reset()
{
	if (m_ptr != nullptr)
	{
		delete m_ptr;
	}
}

template<typename Type>
GE_INLINE Type* TUniquePtr<Type>::Release()
{
	Type* const tempPtr = m_ptr;
	m_ptr = nullptr;
	return tempPtr;
}

template<typename Type>
GE_INLINE void TUniquePtr<Type>::Reset(Type* ptr)
{
	if (ptr != m_ptr)
	{
		delete m_ptr;
		m_ptr = ptr;
	}
}

template<typename Type>
GE_INLINE void TUniquePtr<Type>::Swap(TUniquePtr& other)
{
	Type* const ptr = other.m_ptr;
	other.m_ptr = m_ptr;
	m_ptr = ptr;
}

template<typename Type>
GE_INLINE Type* TUniquePtr<Type>::Get() const
{
	return m_ptr;
}

template<typename Type, typename... Args>
GE_INLINE TUniquePtr<Type> MakeUnique(Args&&... args)
{
	return TUniquePtr<Type>(new Type(std::forward<Args>(args)...));
}