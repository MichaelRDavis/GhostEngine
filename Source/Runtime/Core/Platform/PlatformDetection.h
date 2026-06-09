#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define GE_WINDOWS_PLATFORM
#ifndef _WIN64
	#error "32-bit builds are not supported on Windows!"
#endif
#elif defined(__linix__) || defined(__gun_linux__)
	#define GE_LINUX_PLATFORM
#elif __APPLE__
	#define GE_PLATFORM_MACOS
#if TARGET_IPHONE_SIMULATOR
	#error "IPhone builds are not supoorted!"
#elif TARGET_OS_IPHONE
	#error "IPhone builds are not supoorted!"
#elif 
	#define GE_PLATFORM_MACOS
#else 
	#error "Unknown platform not supported!"
#endif
#endif