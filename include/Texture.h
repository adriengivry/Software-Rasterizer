#pragma once
#include "Color.h"

class Texture
{
public:
	Texture(const uint16_t p_width, const uint16_t p_height, const uint8_t p_r = 0, const uint8_t p_g = 0, const uint8_t p_b = 0, const uint8_t p_a = 255);
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