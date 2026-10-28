#pragma once

#ifdef _MSC_VER
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

#define GHOST_MSVC_COMPILER 
#define GHOST_INLINE __inline
#define GHOST_FORCEINLINE __forceinline
#define GHOST_NOINLINE __declspec(noinline)
#define GHOST_DLLEXPORT __declspec(dllexport)
#define GHOST_DLLIMPORT __declspec(dllimport)
#define GHOST_NULL nullptr
#endif