#pragma once

#include "CoreExport.h"
#include "Core.h"
#include "MemoryTags.h"

struct MemoryStats
{
	U64 totalAllocated;
	U64 taggedAllocations[MEM_TAG_Max];
};

class CORE_API CMemoryTracker
{
public:
	static void Init();

	static void Destroy();

	static void AddAllocation(U64 size, EMemoryTag tag);
	
	static void RemoveAllocation(U64 size, EMemoryTag tag);

	static char* GetMemoryUsage();

private:
	static MemoryStats m_memoryStats;
};