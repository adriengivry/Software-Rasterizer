#include "../include/Texture.h"

Texture::Texture(const uint16_t p_width, const uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_pixels(new Color(0, 0, 0, 255)) {}

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