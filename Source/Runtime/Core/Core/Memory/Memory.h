#pragma once

#include "CoreHeader.h"

class CMemory
{
public:
	static void* Malloc(U64 size, U8 align);

	static void Free(void* ptr, U8 align);

	static void* Memset(void* ptr, I32 value, U64 size);

	static void* Memcpy(void* dest, const void* src, U64 size);
};