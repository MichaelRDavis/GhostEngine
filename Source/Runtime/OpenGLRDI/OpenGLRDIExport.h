#pragma once

#ifdef _MSC_VER
	#ifdef OPENGLRDI_EXPORT
		#define OPENGLRDI_API __declspec(dllexport)
	#else
		#define OPENGLRDI_API __declspec(dllimport)
	#endif
#endif