#pragma once

#ifdef RDI_EXPORT
	#define RDI_API __declspec(dllexport)
#else
	#define RDI_API __declspec(dllimport)
#endif