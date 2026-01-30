#pragma once

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif __linux__
#include <SDL3/SDL.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include <new>