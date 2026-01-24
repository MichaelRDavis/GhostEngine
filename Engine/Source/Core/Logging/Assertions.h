#pragma once

#include "Platform/Platform.h"

void AssertFailed(const char* file, I32 line, const char* expr);

#ifdef _DEBUG
	#define GE_ASSERT(expr) AssertFailed(__FILE__, __LINE__, #expr);
	#define GE_CHECK(expr) expr ? true : (AssertFailed(__FILE__, __LINE__, #expr), false)
#else
	#define GE_ASSERT(expr)
	#define GE_CHECK(expr)
#endif