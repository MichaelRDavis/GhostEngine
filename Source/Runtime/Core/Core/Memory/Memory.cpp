#include "Memory.h"

void* CMemory::Malloc(U64 size, U8 align)
{
	return malloc(size);
}

void CMemory::Free(void* ptr, U8 align)
{
	free(ptr);
}

void* CMemory::Memset(void* ptr, I32 value, U64 size)
{
	return memset(ptr, 0, size);
}

void* CMemory::Memcpy(void* dest, const void* src, U64 size)
{
	return memcpy(dest, src, size);
}