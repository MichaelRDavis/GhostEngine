#pragma once

#include "Core.h"

class CMath
{
public:
	template<typename Type>
	static const Type& Min(const Type& a, const Type& b)
	{
		return (b < a) ? b : a;
	}

	template<typename Type>
	static const Type& Max(const Type& a, const Type& b)
	{
		return (a < b) ? b : a;
	}
};