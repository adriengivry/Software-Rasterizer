#include <SDL.h>
#include <cstdlib>

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		// TODO Core of the program
		SDL_Quit();
	}
	else
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
