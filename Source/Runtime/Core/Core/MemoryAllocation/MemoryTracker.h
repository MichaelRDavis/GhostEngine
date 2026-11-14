#pragma once

#include "Core.h"
#include "MemoryTags.h"

struct SAllocation
{
	U64 size;
	const char* file;
	I32 line;
	EMemoryTag tag;
};

class CORE_API CMemoryTracker
{
public:
	static void Init(U64 maxMemAllocations);

	static void AddAllocation(void* ptr, U64 size, const char* file, I32 line, EMemoryTag tag = EMemoryTag::MEMTAG_None);

	static void RemoveAllocation(void* ptr);

	static void ReportAllocations();

private:
	static std::unordered_map<void*, SAllocation> mAllocations;
	static U64 mMemoryAllocated;
	static U64 mMaxMemoryAllocations;
};