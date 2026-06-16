#pragma once

struct ViewportInfo;
class IRDI;

enum class EGraphicsAPI
{
	OpenGL,
	Vulkan
};

struct EngineConfig
{
	EGraphicsAPI graphicsAPI;
};

class CEngine
{
public:
	CEngine();
	~CEngine();

	virtual bool Init(const EngineConfig& config, const ViewportInfo& viewport);
	virtual void Update();
	virtual void Destroy();

protected:
	EngineConfig mEngineConfig;

	IRDI* mRenderer;
};