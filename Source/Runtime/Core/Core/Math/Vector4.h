#pragma once

#include "Core.h"

struct SVector4
{
	SVector4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{

	}

	SVector4(F32 inX, F32 inY, F32 inZ, F32 inW)
		: x(inX)
		, y(inY)
		, z(inZ)
		, w(inW)
	{

	}

	F32 x;
	F32 y;
	F32 z;
	F32 w;
};