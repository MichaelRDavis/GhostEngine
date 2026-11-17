#pragma once

#include "Core.h"
#include "MemoryTags.h"

class CORE_API CMemory
{
public:
	static void* Allocate(U64 size, EMemoryTag memTag = EMemoryTag::MEMTAG_None, U64 alignment = 0, bool isAligned = false);

	static void* Reallocate(void* ptr, U64 size, EMemoryTag memTag = EMemoryTag::MEMTAG_None, U64 alignment = 0, bool isAligned = false);

	static void Free(void* ptr, bool isAligned = false);

	static void* Set(void* ptr, I32 value, U64 size);

	static void* Zero(void* ptr, U64 size);

	static void* Copy(void* dest, const void* src, U64 size);
};

#pragma warning(push)
#pragma warning(disable : 4595)
GHOST_INLINE void *operator new(size_t size) { return CMemory::Allocate(size, EMemoryTag::MEMTAG_New); }
GHOST_INLINE void operator delete(void* ptr) { CMemory::Free(ptr); }
#pragma warning(pop)