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

	int initPng = IMG_INIT_PNG;
	if (IMG_Init(initPng) != IMG_INIT_SUCCESS)
	{
		SDL_LOG("Failed to Init Image");
		success = false;
	}
	return success;
}

void Toolbox::CloseSDL()
{
	TTF_Quit();
	SDL_Quit();
}
