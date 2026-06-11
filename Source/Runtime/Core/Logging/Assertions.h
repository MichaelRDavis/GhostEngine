#pragma once

#include "Core.h"

bool32 ReportAssertion(const char* expr, const char* msg, const char* file, int32 line);

#define GE_ASSERT(expr) ReportAssertion(expr, "", __FILE__, __LINE__);
#define GE_CHECK(expr) ((expr) ? TRUE : (ReportAssertion(expr, "", __FILE__, __LINE__), FALSE));