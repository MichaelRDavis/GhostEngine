#pragma once

#include "Platform/Platform.h"

struct Vec3
{
	Vec3();
	Vec3(F32 inX, F32 inY, F32 inZ);

	Vec3& operator=(float value);

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;

	F32 x;
	F32 y;
	F32 z;
};