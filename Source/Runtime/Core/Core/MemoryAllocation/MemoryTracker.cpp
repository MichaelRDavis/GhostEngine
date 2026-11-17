#include "MemoryTracker.h"

std::unordered_map<void*, SAllocation> CMemoryTracker::mMemoryAllocations;

void CMemoryTracker::Init()
{
	
}

void CMemoryTracker::TrackMemAlloc(void* ptr, U64 size, const char* file, I32 line, EMemoryTag tag)
{

}

void CMemoryTracker::UntrackMemAlloc(void* ptr)
{

}

void CMemoryTracker::ReportMemAlloc()
{
	
}