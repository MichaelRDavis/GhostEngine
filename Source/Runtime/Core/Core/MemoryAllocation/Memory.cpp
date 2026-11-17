#include "Memory.h"

void* CMemory::Allocate(U64 size, EMemoryTag memTag, U64 alignment, bool isAligned)
{
	void* ptr = nullptr;

	if (isAligned)
	{
#ifdef GHOST_PLATFORM_WINDOWS
		ptr = _aligned_malloc(size, alignment);
		GHOST_TRACKMEMORY(ptr, memTag);
		return ptr;
#endif
	}

	ptr = malloc(size);
	GHOST_TRACKMEMORY(ptr, memTag);
	return ptr;
}

void* CMemory::Reallocate(void* ptr, U64 size, EMemoryTag memTag, U64 alignment, bool isAligned)
{
	GHOST_UNTRACKMEMORY(ptr);
	void* newPtr = nullptr;

	if (isAligned)
	{
#ifdef GHOST_PLATFORM_WINDOWS
		newPtr = _aligned_realloc(ptr, size, alignment);
		GHOST_TRACKMEMORY(newPtr, memTag);
		return newPtr;
#endif
	}

	newPtr = realloc(ptr, size);
	GHOST_TRACKMEMORY(newPtr, memTag);
	return newPtr;
}

void CMemory::Free(void* ptr, bool isAligned)
{
	if (isAligned)
	{
#ifdef GHOST_PLATFORM_WINDOWS
		GHOST_UNTRACKMEMORY(ptr);
		_aligned_free(ptr);
#endif
	}
	else
	{
		GHOST_UNTRACKMEMORY(ptr);
		free(ptr);
	}
}

void* CMemory::Set(void* ptr, I32 value, U64 size)
{
	return memset(ptr, value, size);
}

void* CMemory::Zero(void* ptr, U64 size)
{
	return memset(ptr, 0, size);
}

void* CMemory::Copy(void* dest, const void* src, U64 size)
{
	return memcpy(dest, src, size);
}