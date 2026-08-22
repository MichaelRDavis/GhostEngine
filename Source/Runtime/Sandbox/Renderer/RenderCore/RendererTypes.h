#pragma once

#include "Platform/PlatformHeader.h"
#include "Core/CoreHeader.h"

enum EBufferUsage
{
	Static,
	Dynamic
};

struct FMesh
{
	std::vector<FVec3> vertices;
	std::vector<U32> indices;
};

struct FVeretxBuffer
{
	U32 bufferID;
	U32 size;
	void* data;
};

struct FIndexBuffer
{
	U32 bufferID;
	U32 size;
	void* data;
};