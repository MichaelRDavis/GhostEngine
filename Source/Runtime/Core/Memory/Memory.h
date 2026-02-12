#pragma once

#include "CoreExport.h"
#include "Core.h"
#include "MemoryTags.h"

class CORE_API CMemory
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

#pragma warning(push)
#pragma warning(disable : 4595)
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
#pragma warning(pop)