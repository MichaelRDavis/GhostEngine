#pragma once

#include "Core.h"

bool AssertFailed(const char* file, I32 line, const char* expression);

#if defined(GHOST_DEBUG_EDITOR) || defined(GHOST_DEBUG_GAME)
#define GHOST_ASSERT(x) (void)((!!(x)) || (AssertFailed(__FILE__, __LINE__, #x)));
#define GHOST_CHECK(x) ((x) ? true : (AssertFailed(__FILE__, __LINE__, #x), false));
#else
#define GHOST_ASSERT(x) (( void )0);
#define GHOST_CHECK(x) (( x ) ? true : false);
#endif