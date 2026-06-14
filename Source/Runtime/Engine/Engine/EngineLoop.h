#pragma once

#ifdef ENGINE_EXPORT
	#define ENGINE_API __declspec(dllexport)
#else
	#define ENGINE_API __declspec(dllimport)
#endif

class CEngine;

class ENGINE_API CEngineLoop
{
public:
	CEngineLoop();
	~CEngineLoop();

	void Init();

	void Update();

	void Destroy();

private:
	bool mIsInitialised;
};

extern CEngine* gEngine = nullptr;

inline const CEngine* GetEngine()
{
	if (gEngine != nullptr)
	{
		return gEngine;
	}

	return nullptr;
}