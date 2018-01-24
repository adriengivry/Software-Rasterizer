#include "Window.h"

Window::Window()
{
	m_windowComponent = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	m_renderer = SDL_CreateRenderer(m_windowComponent, -1, SDL_RENDERER_ACCELERATED);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

Window::~Window()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_windowComponent);
}

SDL_Window* Window::GetWindowComponent() const { return m_windowComponent; }
SDL_Renderer* Window::GetRenderer() const { return m_renderer; }
SDL_Texture* Window::GetTexture() const { return m_texture; }