#include "MemoryTracker.h"
#include "Logging/Log.h"
#include "Memory/Memory.h"

MemoryStats CMemoryTracker::m_memoryStats = { };

void CMemoryTracker::Init()
{
	
}

void CMemoryTracker::Destroy()
{
	
}

void CMemoryTracker::AddAllocation(U64 size, EMemoryTag tag)
{
	if (tag == MEM_TAG_None)
	{
		GE_LOG(Warning, "Memory Tracker: Memory allocated with MEM_TAG_None.");
	}

	m_memoryStats.totalAllocated += size;
	m_memoryStats.taggedAllocations[tag] += size;
}

void CMemoryTracker::RemoveAllocation(U64 size, EMemoryTag tag)
{
	if (tag == MEM_TAG_None)
	{
		GE_LOG(Warning, "Memory Tracker: Memory deallocated with MEM_TAG_None.");
	}

	m_memoryStats.totalAllocated -= size;
	m_memoryStats.taggedAllocations[tag] -= size;
}

char* CMemoryTracker::GetMemoryUsage()
{
	const U64 gib = 1024 * 1024 * 1024;
	const U64 mib = 1024 * 1024;
	const U64 kib = 1024;

	char buffer[8000] = "Memory Tracker: Memory Allocated (tagged):\n";
	U64 offset = strlen(buffer);

	for (U32 i = 0; i < MEM_TAG_Max; ++i)
	{
		char unit[4] = "xiB";
		F64 amount = 1.0f;

		if (m_memoryStats.taggedAllocations[i] >= gib)
		{
			unit[0] = 'G';
			amount = m_memoryStats.taggedAllocations[i] / (F64)gib;
		}
		else if (m_memoryStats.taggedAllocations[i] >= mib)
		{
			unit[0] = 'M';
			amount = m_memoryStats.taggedAllocations[i] / (F64)mib;
		}
		else if (m_memoryStats.taggedAllocations[i] >= kib)
		{
			unit[0] = 'K';
			amount = m_memoryStats.taggedAllocations[i] / (F64)kib;
		}
		else
		{
			unit[0] = 'B';
			unit[1] = 0;
			amount = (F64)m_memoryStats.taggedAllocations[i];
		}

		I32 length = snprintf(buffer + offset, 8000, "	%s: %.2f%s\n", MemoryTagStrings[i], amount, unit);
		offset += length;
	}

	char* outBuffer = _strdup(buffer);
	return outBuffer;
}
