#pragma once

#ifdef VULKANRDI_EXPORT
	#define VULKANRDI_API __declspec(dllexport)
#else
	#define VULKANRDI_API __declspec(dllimport)
#endif