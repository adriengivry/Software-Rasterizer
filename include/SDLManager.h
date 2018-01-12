#pragma once

#define SDL_INIT_SUCCESS 0
#define TTF_INIT_SUCCESS 0
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl

namespace Toolbox
{
	bool InitSDL();
	void CloseSDL();
}