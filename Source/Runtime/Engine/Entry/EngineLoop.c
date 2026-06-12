#include "Core.h"

int main()
{
	GE_LOG(Fatal, "Hello World!");
	GE_LOG(Error, "Hello World!");
	GE_LOG(Warning, "Hello World!");
	GE_LOG(Display, "Hello World!");
	GE_LOG(Log, "Hello World!");
	GE_LOG(Verbose, "Hello World!");
	GE_LOG(VeryVerbose, "Hello World!");

	FWindowDefinition windowDefinition;
	windowDefinition.title = "Engine";
	windowDefinition.winWidth = 1920;
	windowDefinition.winHeight = 1080;

	FApplication app;

	App_Init(&app, &windowDefinition);

	while (TRUE)
	{
		App_Run(&app);
	}

	return 0;
}