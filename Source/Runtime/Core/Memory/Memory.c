#include "Memory.h"

void* Mem_Alloc(uint64 size, bool8 aligned)
{
	return malloc(size);
}

void Mem_Free(void* ptr, bool8 aligned)
{
	free(ptr);
}

void* Mem_Zero(void* ptr, uint64 size)
{
	return memset(ptr, 0, size);
}

void* Mem_Copy(void* dest, const void* src, uint64 size)
{
	return memcpy(dest, src, size);
}

void* Mem_Set(void* dest, int32 value, uint64 size)
{
	return memset(dest, value, size);
}