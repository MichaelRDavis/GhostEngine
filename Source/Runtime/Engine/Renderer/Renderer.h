#pragma once

struct RendererInfo
{
	void* context;
} typedef RendererInfo;

int Renderer_CreateContext(struct Window* window, RendererInfo* info);
void Renderer_Clear();
void Renderer_SwapBuffers(struct Window* window);
