#include "../include/Rasterizer.h"

Rasterizer::Rasterizer(Texture & p_texture) :
	m_window(nullptr),
	m_renderer(nullptr),
	m_texture(nullptr),
	m_rtexture(p_texture)
{}

Rasterizer::~Rasterizer()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Rasterizer::RenderScene(Scene * p_pScene)
{

}
void Rasterizer::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow
	(
		"Rasterizer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_rtexture.GetWidth(),
		m_rtexture.GetHeight(),
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
		SDL_PIXELFORMAT_ARGB32,
		SDL_TEXTUREACCESS_STREAMING,
		m_rtexture.GetWidth(),
		m_rtexture.GetHeight()
	);

	SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
}

void Rasterizer::update()
{
	SDL_UpdateTexture(m_texture, nullptr, m_rtexture.GetPixelBuffer(), m_rtexture.GetWidth() * sizeof(uint32_t));
	SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
	m_rtexture.ClearBuffer();
	SDL_RenderClear(m_renderer);
}

void Rasterizer::drawLine(float p_x1, float p_y1, float p_x2, float p_y2, Color& p_color1, Color& p_color2)
{
	float dx = p_x2 - p_x1;
	float dy = p_y2 - p_y1;
	float dx1 = fabs(p_x2 - p_x1);
	float dy1 = fabs(p_y2 - p_y1);
	if (dx == 0.0f && dy == 0.0f)
	{
		m_rtexture.SetPixelColor(p_x1, p_y1, p_color1);
		return;
	}
	float index = 0;
	if (fabs(dx) > fabs(dy))
	{
		float xMin, xMax;
		if (p_x1 < p_x2)
		{
			xMin = p_x1;
			xMax = p_x2;
		}
		else
		{
			xMin = p_x2;
			xMax = p_x1;
		}
		float slope = dy / dx;
		for (uint16_t x = xMin; x <= xMax; x++)
		{
			float y = p_y1 + ((x - p_x1) * slope);
			if (xMin == p_x1)
			{
				Color color = p_color1 * ((dx1 - index)/dx1);
				Color color1 = p_color2 * (index/dx1);
				m_rtexture.SetPixelColor(x, y, color + color1);
			}
			else if (xMin == p_x2)
			{
				Color color = p_color2 * ((dx1 - index)/dx1);
				Color color1 = p_color1 * (index/dx1);
				m_rtexture.SetPixelColor(x, y, color + color1);
			}
			++index;
	    }
	}
	else
	{	
		float yMin, yMax;
		if (p_y1 < p_y2)
		{
			yMin = p_y1;
			yMax = p_y2;
		}
		else
		{
			yMin = p_y2;
			yMax = p_y1;
		}
		float slope = dx / dy;
		for (uint16_t y = yMin; y <= yMax; y++)
		{
			float x = p_x1 + ((y - p_y1) * slope);
			if (yMin == p_y1)
			{
				Color color = ((p_color2 / dy1) * (index));
				Color color1 = ((p_color1 / dy1) * (dy1 - index));
				m_rtexture.SetPixelColor(x, y, (color + color1));
			}
			else if (yMin == p_y2)
			{
				Color color = ((p_color1 / dy1) * (index));
				Color color1 = ((p_color2 / dy1) * (dy1 - index));
				m_rtexture.SetPixelColor(x, y, (color + color1));
			}
			++index;
		}
	}
}