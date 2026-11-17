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
	static void Init();

	static void TrackMemAlloc(void* ptr, U64 size, const char* file, I32 line, EMemoryTag tag);

	static void UntrackMemAlloc(void* ptr);

	static void ReportMemAlloc();

private:
	static std::unordered_map<void*, SAllocation> mMemoryAllocations;
};

#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_DEBUG_GAME)
#define GHOST_TRACKMEMORY(x, tag) CMemoryTracker::TrackMemAlloc(x, sizeof(x), __FILE__, __LINE__, tag);
#define GHOST_UNTRACKMEMORY(x) CMemoryTracker::UntrackMemAlloc(x);
#else 
#define GHOST_TRACKMEMORY(x, tag)
#define GHOST_UNTRACKMEMORY(x)
#endif