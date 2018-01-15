#include "SDLManager.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>


bool Toolbox::InitSDL()
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

	int flag = IMG_INIT_PNG;
	int initted = IMG_Init(flag);
	if (initted&flag != flag)
	{
		SDL_LOG("Failed to Init Image");
		success = false;
	}
	return success;
}

void Toolbox::CloseSDL()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
