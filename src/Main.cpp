#include "SDLManager.h"
#include "Application.h"

int main(int argc, char* argv[])
{
	if (!Toolbox::InitSDL())
	{
		Toolbox::CloseSDL();
		return EXIT_FAILURE;
	}

	Application app;

	while (app.GetContext().appInfos.isRunning)
	{
		app.Update();
		app.Draw();
	}

	Toolbox::CloseSDL();

	return EXIT_SUCCESS;
}
