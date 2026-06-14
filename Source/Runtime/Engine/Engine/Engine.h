#pragma once

class IRDI;

class CEngine
{
public:
	CEngine();
	~CEngine();

	virtual bool Init();
	virtual void Update();
	virtual void Destroy();

protected:
	IRDI* mRenderer;
};