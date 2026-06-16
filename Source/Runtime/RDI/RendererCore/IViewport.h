#pragma once

struct ViewportInfo
{
	void* surface;
	int width;
	int height;
};

class IViewport
{
public:
	IViewport() {}
	~IViewport() {}

	virtual void CreateViewport(const ViewportInfo& info) {}
	virtual void DestroyViewport() {}

protected:
	ViewportInfo mViewportInfo = {};
};