#pragma once

#include "Platform/PlatformHeader.h"
#include "Core/CoreHeader.h"

struct FMesh
{
	std::vector<FVec3> vertices;
};

struct FVeretxBuffer
{
	U32 bufferID;
	U32 size;
	void* data;
};