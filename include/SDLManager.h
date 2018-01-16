#pragma once

#include "IManager.h"

#define SDL_INIT_SUCCESS 0
#define TTF_INIT_SUCCESS 0
#define IMG_INIT_SUCCESS 1
#define SDL_LOG(logMessage) std::cout << "[SDL] " << logMessage << std::endl

class SDLManager : public IManager
{
public:
	SDLManager() { SDLManager::Setup(); }
	~SDLManager() { SDLManager::Close(); }

	void Setup() override;
	void Close() override;
	void Update() override;

	bool InitSucceed() const;
private:
	bool m_initSuccess;
};