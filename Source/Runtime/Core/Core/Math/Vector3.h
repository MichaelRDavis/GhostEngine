#pragma once

#include "Core.h"

struct SVector3
{
	SVector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{

	}

	SVector3(F32 inX, F32 inY, F32 inZ)
		: x(inX)
		, y(inY)
		, z(inZ)
	{

	}

	F32 x;
	F32 y;
	F32 z;
};