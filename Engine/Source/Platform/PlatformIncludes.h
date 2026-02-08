#pragma once

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif __linux__
#include <SDL3/SDL.h>
#endif

// C header includes 
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

// C++ standard library header includes
#include <new>
#include <vector>			// TDOO: Remove replace with GhostLib TArrayList
#include <unordered_map>	// TODO: Remove replace with GhostLib THashMap
#include <algorithm>
#include <array>
#include <fstream>