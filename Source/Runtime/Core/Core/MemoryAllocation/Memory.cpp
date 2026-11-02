#include "Memory.h"

void* CMemory::Allocate(U64 size, U64 alignment, bool isAligned)
{
	if (isAligned)
	{
#ifdef GHOST_SYSTEM_WINDOWS
		return _aligned_malloc(size, alignment);
#endif
	}

	return malloc(size);
}

void* CMemory::Reallocate(void* ptr, U64 size, U64 alignment, bool isAligned)
{
	if (isAligned)
	{
#ifdef GHOST_SYSTEM_WINDOWS
		return _aligned_realloc(ptr, size, alignment);
#endif
	}

	return realloc(ptr, size);
}

void CMemory::Free(void* ptr, bool isAligned)
{
	if (isAligned)
	{
#ifdef GHOST_SYSTEM_WINDOWS
		_aligned_free(ptr);
#endif
	}
	else
	{
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