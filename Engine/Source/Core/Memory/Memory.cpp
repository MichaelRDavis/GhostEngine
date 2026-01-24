#include "Memory.h"

void* CMemory::Malloc(U64 size)
{
	return malloc(size);
}

void* CMemory::AlignedMalloc(U64 size, U8 alignment)
{
#ifdef GE_WINDOWS_PLATFORM
	return _aligned_malloc(size, alignment);
#endif
	return nullptr;
}

void* CMemory::Memcpy(void* dest, const void* src, U64 size)
{
	return memcpy(dest, src, size);
}

void* CMemory::Memset(void* dest, I32 value, U64 size)
{
	return memset(dest, value, size);
}

void* CMemory::Zero(void* dest, U64 size)
{
	return memset(dest, 0, size);
}

void CMemory::Free(void* ptr)
{
	free(ptr);
}

void CMemory::AlignedFree(void* ptr)
{
#ifdef GE_WINDOWS_PLATFORM
	_aligned_free(ptr);
#endif
}