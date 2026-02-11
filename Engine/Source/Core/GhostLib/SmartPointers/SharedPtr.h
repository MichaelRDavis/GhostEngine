#pragma once

#include "Platform/Platform.h"

template<typename Type>
class TSharedPtr
{
private:
	struct SharedCount
	{
		U32 counter = 0;

		void Add()
		{
			counter++;
		}

		void Sub()
		{
			--counter;
		}
	};

public:
	TSharedPtr();
	explicit TSharedPtr(Type* ptr);
	TSharedPtr(const Type& other);
	~TSharedPtr();

	TSharedPtr& operator=(const Type& other);

	Type& operator*() const;
	Type* operator->() const;

	explicit operator bool() const;

	void Release();
	void Reset(Type* ptr = nullptr);
	void Swap(TSharedPtr& other);

	Type* Get() const;

private:
	Type* m_ptr;
	SharedCount m_counter;
};

template<typename Type>
GE_INLINE TSharedPtr<Type>::TSharedPtr()
	: m_ptr(nullptr)
{
	
}

template<typename Type>
GE_INLINE TSharedPtr<Type>::TSharedPtr(Type* ptr)
	: m_ptr(ptr)
{

}

template<typename Type>
GE_INLINE TSharedPtr<Type>::TSharedPtr(const Type& other)
	: m_ptr(other.m_ptr)
	, m_counter(other.m_counter)
{
	if (m_ptr != nullptr)
	{
		m_counter.Add();
	}
}

template<typename Type>
GE_INLINE TSharedPtr<Type>::~TSharedPtr()
{
	Release();
}

template<typename Type>
GE_INLINE TSharedPtr<Type>& TSharedPtr<Type>::operator=(const Type& other)
{
	Release();

	m_ptr = other.m_ptr;
	m_counter = other.m_counter;

	m_counter.Add();

	return *this;
}

template<typename Type>
GE_INLINE Type& TSharedPtr<Type>::operator*() const
{
	return &m_ptr;
}

template<typename Type>
GE_INLINE Type* TSharedPtr<Type>::operator->() const
{
	return m_ptr;
}

template<typename Type>
GE_INLINE TSharedPtr<Type>::operator bool() const
{
	return m_ptr != nullptr && m_counter > 0;
}

template<typename Type>
GE_INLINE void TSharedPtr<Type>::Reset(Type* ptr)
{
	Release();

	m_ptr = ptr;
	m_counter.counter = 0;

	m_counter.Add();
}

template<typename Type>
GE_INLINE void TSharedPtr<Type>::Swap(TSharedPtr& other)
{
	m_ptr = other.m_ptr;
	m_counter = other.m_counter;
}

template<typename Type>
GE_INLINE Type* TSharedPtr<Type>::Get() const
{
	return m_ptr;
}

template<typename Type>
GE_INLINE void TSharedPtr<Type>::Release()
{
	m_counter.Sub();

	if (m_counter.counter == 0)
	{
		delete m_ptr;
		m_ptr = nullptr;
	}
}

template<typename Type, typename... Args>
GE_INLINE TSharedPtr<Type> MakeShared(Args&&... args)
{
	return TSharedPtr<Type>(new Type(std::forward<Args>(args)...));
}