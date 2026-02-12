#include "Vec4.h"

Vec4::Vec4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vec4::Vec4(F32 inX, F32 inY, F32 inZ, F32 inW)
	: x(inX)
	, y(inY)
	, z(inZ)
	, w(inW)
{

}