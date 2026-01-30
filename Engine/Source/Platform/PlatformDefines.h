#pragma once

#ifdef _MSC_VER
#define GE_INLINE __inline
#define GE_FORCEINLINE __forceinline
#elif __GNUC__
#define GE_INLINE inline
#define GE_FORCEINLINE __attribute__((__always_inline__))
#endif