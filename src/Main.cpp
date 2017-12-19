#include <SDL.h>
#include <cstdlib>
#include <iostream>

#define SDL_INIT_SUCCESS 0
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl

int SDL_main(int argc, char** argv)
{
	{
		SDL_LOG("Attempting to init");
		if (SDL_Init(SDL_INIT_VIDEO) != SDL_INIT_SUCCESS)
		{
			SDL_LOG("Initialization failed");
			return EXIT_FAILURE;
		}

		SDL_LOG("Initialization succeed");

		// TODO Core of the program

		SDL_Quit();
		SDL_LOG("Closed");
	}

	system("pause");

	return EXIT_SUCCESS;
}
