#pragma once
#include "Color.h"
#include <SDL.h>
#include <string>
#include <SDL_image.h>


class Texture
{
public:
	Texture(const uint16_t p_width, const uint16_t p_height);
	~Texture();

	void SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color);
	Color GetPixelColor(const uint16_t p_x, const uint16_t p_y);
	Color CalculatePixelColor(const uint32_t pixel);
	uint16_t GetWidth();
	uint16_t GetHeight();
	Color* GetColor();
	void SetColor(Color* p_pColor);
	uint32_t* GetPixelBuffer();
	void ClearBuffer();

private:
	SDL_Surface * m_rbga;
	uint32_t* m_pixelBuffer;
	uint16_t m_width;
	uint16_t m_height;
	Color* m_palette;
};