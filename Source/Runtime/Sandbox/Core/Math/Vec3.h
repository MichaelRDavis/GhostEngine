#pragma once

#include "Platform/PlatformHeader.h"

struct FVec3
{
	FVec3(F32 inX, F32 inY, F32 inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}

	F32 x;
	F32 y;
	F32 z;
};