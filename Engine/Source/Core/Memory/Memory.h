#pragma once

#include "Platform/Platform.h"
#include "MemoryTags.h"

class CMemory
{
public:
	static void* Malloc(U64 size, EMemoryTag tag = MEM_TAG_None);

	static void* AlignedMalloc(U64 size, U8 alignment, EMemoryTag tag = MEM_TAG_None);

	static void* Memcpy(void* dest, const void* src, U64 size);

	static void* Memset(void* dest, I32 value, U64 size);

	static void* Zero(void* dest, U64 size);

	static void Free(void* ptr, EMemoryTag tag = MEM_TAG_None);

	static void AlignedFree(void* ptr, EMemoryTag tag = MEM_TAG_None);
};

GE_INLINE void* operator new(size_t size)
{
	return CMemory::Malloc(size, MEM_TAG_New);
}

GE_INLINE void operator delete(void* ptr)
{
	CMemory::Free(ptr, MEM_TAG_New);
}

GE_INLINE void* operator new[](size_t size)
{
	return CMemory::Malloc(size, MEM_TAG_New);
}

GE_INLINE void operator delete[](void* ptr)
{
	CMemory::Free(ptr, MEM_TAG_New);
}

GE_INLINE void* operator new(size_t size, EMemoryTag tag)
{
	return CMemory::Malloc(size, tag);
}

GE_INLINE void operator delete(void* ptr, EMemoryTag tag)
{
	CMemory::Free(ptr, tag);
}

GE_INLINE void* operator new[](size_t size, EMemoryTag tag)
{
	return CMemory::Malloc(size, tag);
}

GE_INLINE void operator delete[](void* ptr, EMemoryTag tag)
{
	CMemory::Free(ptr, tag);
}