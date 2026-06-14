#pragma once

#ifdef RDI_EXPORT
	#define RDI_API __declspec(dllexport)
#else
	#define RDI_API __declspec(dllimport)
#endif

class RDI_API IRDI
{
public:
	IRDI() {}
	virtual ~IRDI() {}

	virtual void Init() {}
	virtual void Render() {}
	virtual void Destroy() {}
};