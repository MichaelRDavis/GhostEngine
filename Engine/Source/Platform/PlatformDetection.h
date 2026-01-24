#pragma once

#ifdef _WIN32
	#ifdef _WIN64
		#define GE_WINDOWS_PLATFORM
	#else
		#error "32-bit (x86) builds are not supported on Windows!"
	#endif
#else 
	#error "Platform not supported!"
#endif

#ifdef _MSC_VER
	#define GE_MSVC_COMPILER
#else
	#error "Compiler not supported!"
#endif