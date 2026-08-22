#pragma once

#ifdef _MSC_VER
	#define GE_MSVC_COMPILER
#else 
	#error "Compiler not supported!"
#endif

#ifdef _WIN64
	#define GE_WINDOWS_PLATFORM
#else 
	#error "Bulld platform not supported!"
#endif

#ifdef GE_MSVC_COMPILER
typedef __int8 I8;
typedef __int16 I16;
typedef __int32 I32;
typedef __int64 I64;
typedef unsigned __int8 U8;
typedef unsigned __int16 U16;
typedef unsigned __int32 U32;
typedef unsigned __int64 U64;
typedef float F32;
typedef double F64;

#define GE_INLINE __inline
#define GE_FORCEINLINE __forceinline
#endif