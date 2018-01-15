#include "../include/Texture.h"

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

void Texture::SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color)
{
	if (p_x >= m_width || p_y >= m_height)
	{
		return;
	}
	if (p_x < 0 || p_y < 0)
	{
		return;
	}
		m_pixelBuffer[p_y * m_width + p_x] = p_color.CovertTo32();
}

Color Texture::GetPixelColor(const uint16_t p_x, const uint16_t p_y)
{
		uint32_t pixel	= m_pixelBuffer[p_y * m_width + p_x];
		return CalculatePixelColor(pixel);
}

Color Texture::CalculatePixelColor(const uint32_t p_pixel)
{
	uint32_t index = 0;
	uint8_t red, green, blue, alpha;
	
	red = p_pixel >> 8;
	green = p_pixel >> 16;
	blue = p_pixel >> 24;

	Color temp;
	temp.r = red;
	temp.g = green;
	temp.b = blue;
	temp.a = 255.0f;

	return temp;
}

uint16_t Texture::GetWidth()
{
	return m_width;
}

uint16_t Texture::GetHeight()
{
	return m_height;
}

Color* Texture::GetColor()
{
	return m_palette;
}

void Texture::SetColor(Color* p_pColor)
{
	m_palette = p_pColor;
}

uint32_t* Texture::GetPixelBuffer()
{
	return m_pixelBuffer;
}

void Texture::ClearBuffer()
{
	SDL_memset(m_pixelBuffer, 0, m_width * m_height * sizeof(uint32_t));
}
