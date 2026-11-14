#include "MemoryTracker.h"

std::unordered_map<void*, SAllocation> CMemoryTracker::mAllocations;
U64 CMemoryTracker::mMemoryAllocated = 0;
U64 CMemoryTracker::mMaxMemoryAllocations = 0;

void CMemoryTracker::Init(U64 maxMemAllocations)
{
	mMaxMemoryAllocations = maxMemAllocations;
}

void CMemoryTracker::AddAllocation(void* ptr, U64 size, const char* file, I32 line, EMemoryTag tag)
{
	mMemoryAllocated += size;
	if (mMemoryAllocated >= mMaxMemoryAllocations)
	{
		return;
	}

	mAllocations[ptr] = {size, file, line, tag};
}

void CMemoryTracker::RemoveAllocation(void* ptr)
{

}

void CMemoryTracker::ReportAllocations()
{

}