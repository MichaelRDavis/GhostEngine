#pragma once

// It's okay to ignore this warning since we are not distributing engine libraries
#pragma warning(disable : 4251)

#ifdef CORE_EXPORT
	#define CORE_API __declspec(dllexport)
#else
	#define CORE_API __declspec(dllimport)
#endif