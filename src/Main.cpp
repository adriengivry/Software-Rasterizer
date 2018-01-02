#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include "../include/Display.h"

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

int SDL_main(int argc, char** argv)
{
	Display display;
	display.init();
	display.initScene();
	unsigned int lastTicks = SDL_GetTicks();
	while (gameRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		display.drawLine();
		display.update();

		unsigned int ticks = SDL_GetTicks();
		unsigned int ticksDiff = ticks - lastTicks;
		if (ticksDiff == 0)
			continue;
		
		float time = ticksDiff / 1000.0f;
		lastTicks = ticks;
	}
	return 0;
}
