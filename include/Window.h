#pragma once
#include <SDL.h>

class Window
{
public:
	static const uint16_t WIDTH = 1024;
	static const uint16_t HEIGHT = 768;

	Window();
	~Window();

	SDL_Window* GetWindowComponent() const;
	SDL_Renderer* GetRenderer() const;
	SDL_Texture* GetTexture() const;

private:
	SDL_Window* m_windowComponent;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
};
