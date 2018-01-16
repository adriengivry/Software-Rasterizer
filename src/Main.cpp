#include "SDLManager.h"
#include "Application.h"

int main(int argc, char* argv[])
{
	SDLManager sdlManager;

	if (!sdlManager.InitSucceed())
		return EXIT_FAILURE;
	
	Application app;
	while (app.GetContext().appInfos.isRunning)
	{
		app.Update();
		app.Draw();
	}
	
	return EXIT_SUCCESS;
}
