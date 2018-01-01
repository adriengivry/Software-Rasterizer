#include "../include/Display.h"

Display::Display() : m_pRasterizer{nullptr}, m_pWindow(nullptr), m_pRenderer(nullptr), m_pTexture(nullptr), m_prTexture(nullptr)
{}

Display::~Display()
{
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	delete m_pRasterizer;
	delete m_prTexture;
}

void Display::update()
{
	m_pRasterizer->update();
}

void Display::init()
{
	m_prTexture = new Texture(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pWindow = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);
	m_pRasterizer = new Rasterizer(*m_prTexture, *m_pRenderer, *m_pTexture);
}

void Display::RenderScene(Scene * p_pScene)
{
	m_pRasterizer->RenderScene(p_pScene);
}

void Display::drawLine()
{
	Vertex V0(0, 0, 0);
	V0.SetColor(255, 0 , 0 ,255);
	Vertex V1(-2, 3, 0);
	Vertex V2(2, 4, 0);
	V1.SetColor(0, 255, 0, 255);
	V2.SetColor(0, 0, 255, 255);
	m_pRasterizer->drawTriangle(V0, V1, V2);
}
