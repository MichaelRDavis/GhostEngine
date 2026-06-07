#pragma once

struct Window
{
	const char* title;
	int width;
	int height;
	void* handle;
} typedef Window;

struct App
{
	int bHasQuit;
	Window window;
} typedef App;

int Sys_Init();
void Sys_Quit();
int Sys_CreateWindow(Window* window);
void Sys_DestroyWindow(Window* window);
void Sys_Run(App* app);
