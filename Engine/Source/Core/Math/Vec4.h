#pragma once

#include "Platform/Platform.h"

struct Vec4
{
	Vec4();
	Vec4(F32 inX, F32 inY, F32 inZ, F32 inW);

	F32 x;
	F32 y;
	F32 z;
	F32 w;
};