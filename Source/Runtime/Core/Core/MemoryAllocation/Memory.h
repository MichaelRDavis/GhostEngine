#pragma once

#include "Core.h"

class CORE_API CMemory
{
public:
	static void* Allocate(U64 size, U64 alignment = 0, bool isAligned = false);

	static void* Reallocate(void* ptr, U64 size, U64 alignment = 0, bool isAligned = false);

	static void Free(void* ptr, bool isAligned = false);

	static void* Set(void* ptr, I32 value, U64 size);

	static void* Zero(void* ptr, U64 size);

	static void* Copy(void* dest, const void* src, U64 size);
};