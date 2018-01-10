#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include "../include/Display.h"
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
	return 0;
}
