#pragma once

#include "Core.h"

void* Mem_Alloc(uint64 size, bool8 aligned);
void Mem_Free(void* ptr, bool8 aligned);
void* Mem_Zero(void* ptr, uint64 size);
void* Mem_Copy(void* dest, const void* src, uint64 size);
void* Mem_Set(void* dest, int32 value, uint64 size);