#include "../include/Texture.h"
#include <locale>

Texture::Texture(const uint16_t p_width, const uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_palette(nullptr)
{
	m_pixelBuffer = new uint32_t[m_width * m_height];
	ClearBuffer();
}

Texture::~Texture() 
{
	delete m_pixelBuffer;
	delete m_palette;
}

void Texture::SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color) const
{
	if (p_x < m_width && p_y < m_height)
		m_pixelBuffer[p_y * m_width + p_x] = p_color.CovertTo32();	
}

Color Texture::GetPixelColor(const uint16_t p_x, const uint16_t p_y) const
{
	const uint32_t pixel = m_pixelBuffer[p_y * m_width + p_x];
	return CalculatePixelColor(pixel);
}

Color Texture::CalculatePixelColor(const uint32_t p_pixel)
{
	Color result;
	result.r = static_cast<uint8_t>(p_pixel >> 8);
	result.g = static_cast<uint8_t>(p_pixel >> 16);
	result.b = static_cast<uint8_t>(p_pixel >> 24);
	result.a = 255.0f;
	return result;
}

uint16_t Texture::GetWidth() const
{
	return m_width;
}

uint16_t Texture::GetHeight() const
{
	return m_height;
}

Color* Texture::GetColor() const
{
	return m_palette;
}

void Texture::SetColor(Color* p_pColor)
{
	m_palette = p_pColor;
}

uint32_t* Texture::GetPixelBuffer() const
{
	return m_pixelBuffer;
}

void Texture::ClearBuffer() const
{
	SDL_memset(m_pixelBuffer, 0, m_width * m_height * sizeof(uint32_t));
}
