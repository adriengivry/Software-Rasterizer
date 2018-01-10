#include <SDL.h>
#include "SDL_ttf.h"
#include <cstdlib>
#include <iostream>
#include "Display.h"
#undef main
#define SDL_INIT_SUCCESS 0
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl
static bool gameRunning = true;
static void HandleKeyEvent(const SDL_Event &event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
		gameRunning = false;
		break;
	
	default: break;
	}
}

static void HandleEvent(const SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		gameRunning = false;
		break;
	
	case SDL_KEYDOWN:
		HandleKeyEvent(event);
	default: break;
	}
}

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != SDL_INIT_SUCCESS)
		SDL_LOG("Failed to Init");

	TTF_Init();

	Display display;
	display.Init();
	display.InitScene();

	while (gameRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		display.RenderScene();
		display.Update();
	}

	TTF_Quit();
	SDL_Quit();

	return 0;
}
