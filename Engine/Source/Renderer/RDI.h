#pragma once

class IRDI
{
public:
	IRDI () {}
	~IRDI() {}

	virtual void Init() {}

	virtual void Render() {}

	virtual void Destroy() {}
};