#pragma once

enum EMemoryTag
{
	MEM_TAG_None,
	MEM_TAG_New,
	MEM_TAG_ArrayList,
	MEM_TAG_Max
};

static const char* MemoryTagStrings[MEM_TAG_Max] =
{
	"None ",
	"New ",
	"ArrayList "
};