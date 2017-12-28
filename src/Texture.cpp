#include "../include/Texture.h"

Texture::Texture(const uint16_t p_width, const uint16_t p_height, const uint8_t p_r, const uint8_t p_g, const uint8_t p_b, const uint8_t p_a) :
	m_width(p_width),
	m_height(p_height),
	m_pixels(new Color(p_r, p_g, p_b, p_a)) {}

Texture::~Texture() {}

void Texture::SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color)
{
	m_width = p_x;
	m_height = p_x;
	m_pixels = &p_color;
}

uint16_t Texture::GetWidth()
{
	return m_width;
}

uint16_t Texture::GetHeight()
{
	return m_height;
}

Color * Texture::GetColor()
{
	return m_pixels;
}