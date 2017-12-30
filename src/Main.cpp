#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include "../include/Rasterizer.h"

#define SDL_INIT_SUCCESS 0
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
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
	Texture texture(WINDOW_WIDTH, WINDOW_HEIGHT);
	Rasterizer rast(texture);
	rast.Init();
	float r = 0;
	float x1 = 200.0f;
	float y1 = 300.0f;
	float x2 = 400.0f;
	float y2 = 600.0f;
	float x3 = 800.0f;
	float y3 = 500.0f;
		
	unsigned int lastTicks = SDL_GetTicks();
	while (gameRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvent(event);

		Color color1(255.0f, 0.0f, 0.0f, 255);
		Color color2(0.0f, 255.0f, 0.0f, 255);
		Color color3(0.0f, 0.0f, 255.0f, 255);
		rast.drawLine(x1, y1, x2, y2, color1, color2);
		rast.drawLine(x2, y2, x3, y3, color2, color3);
		rast.drawLine(x3, y3, x1, y1, color3, color1);

		// colors for each point of the triangle
		rast.update();

		unsigned int ticks = SDL_GetTicks();
		unsigned int ticksDiff = ticks - lastTicks;
		
		if (ticksDiff == 0)
			continue;
		
		float time = ticksDiff / 1000.0f;
		lastTicks = ticks;
	}
	return 0;
}
