#pragma once

#ifdef _MSC_VER
	#ifdef CORE_EXPORT
		#define CORE_API __declspec(dllexport)
	#else
		#define CORE_API __declspec(dllimport)
	#endif
#endif