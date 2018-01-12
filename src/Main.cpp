#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include "Application.h"

#define SDL_INIT_SUCCESS 0
#define TTF_INIT_SUCCESS 0
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl

bool InitSDL()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) != SDL_INIT_SUCCESS)
	{
		SDL_LOG("Failed to Init Core");
		success = false;
	}

	if (TTF_Init() != TTF_INIT_SUCCESS)
	{
		SDL_LOG("Failed to Init TTF");
		success = false;
	}

	return success;
}

void CloseSDL()
{
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!InitSDL())
	{
		CloseSDL();
		return EXIT_FAILURE;
	}

	Application app;

	while (app.GetContext().isRunning)
	{
		app.Update();
		app.Draw();
	}

	CloseSDL();

	return EXIT_SUCCESS;
}
