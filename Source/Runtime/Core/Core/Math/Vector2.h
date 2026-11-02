#pragma once

#include "Core.h"

struct SVector2
{
	SVector2()
		: x(0.0f)
		, y(0.0f)
	{
		
	}

	SVector2(F32 inX, F32 inY)
		: x(inX)
		, y(inY)
	{

	}

	F32 x;
	F32 y;
};