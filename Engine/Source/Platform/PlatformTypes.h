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
#elif __GNUC__
typedef char I8;
typedef short I16;
typedef long int I32;
typedef long long int I64;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned long int U32;
typedef unsigned long long int U64;
typedef float F32;
typedef double F64;
#endif