#pragma once
#include "Color.h"

class Texture
{
public:
	Texture(const uint16_t p_width, const uint16_t p_height);
	~Texture();

	void SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color);

	uint16_t GetWidth();
	uint16_t GetHeight();
	Color* GetColor();

private:
	uint16_t m_width;
	uint16_t m_height;
	Color* m_pixels;
};