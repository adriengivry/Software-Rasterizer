#include "SDLManager.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

void SDLManager::Setup()
{
	m_initSuccess = false;

	if (SDL_Init(SDL_INIT_VIDEO) != SDL_INIT_SUCCESS)
	{
		SDL_LOG("Failed to Init Core");
		return;
	}

	if (TTF_Init() != TTF_INIT_SUCCESS)
	{
		SDL_LOG("Failed to Init TTF");
		return;
	}

	const int flag = IMG_INIT_PNG;
	const int initted = IMG_Init(flag);
	if (initted&flag != flag)
	{
		SDL_LOG("Failed to Init Image");
		return;
	}

	m_initSuccess = true;
}

void SDLManager::Close()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDLManager::Update()
{
	// No Update needed for SDLManager
}

bool SDLManager::InitSucceed() const
{
	return m_initSuccess;
}
