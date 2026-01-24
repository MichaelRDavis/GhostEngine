#pragma once

#include "Platform/Platform.h"

class CMemory
{
public:
	static void* Malloc(U64 size);

	static void* AlignedMalloc(U64 size, U8 alignment);

	static void* Memcpy(void* dest, const void* src, U64 size);

	static void* Memset(void* dest, I32 value, U64 size);

	static void* Zero(void* dest, U64 size);

	static void Free(void* ptr);

	static void AlignedFree(void* ptr);
};