#include "../include/Rasterizer.h"

Rasterizer::Rasterizer() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_texture(nullptr)
	{}

Rasterizer::~Rasterizer()
{
	delete m_window;
	delete m_renderer;
	delete m_texture;
}

void Rasterizer::RenderScene(Scene * p_pScene, Texture * p_pTarget)
{

}
void Rasterizer::Init(Texture * p_pTarget)
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow
	(
		"Rasterizer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		p_pTarget->GetWidth(),
		p_pTarget->GetHeight(),
		0
	);

	m_renderer = SDL_CreateRenderer
	(
		m_window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

	m_texture = SDL_CreateTexture
	(
		m_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		p_pTarget->GetWidth(),
		p_pTarget->GetHeight()
	);

}

void Rasterizer::update(Texture* p_pTarget)
{
	SDL_UpdateTexture(m_texture, nullptr, p_pTarget->GetPixelBuffer(), p_pTarget->GetWidth() * sizeof(uint32_t));
	SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
	p_pTarget->ClearBuffer();
}

void Rasterizer::drawLine(float p_x1, float p_y1, float p_x2, float p_y2, uint32_t p_color)
{
}
