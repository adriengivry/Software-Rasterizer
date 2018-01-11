#include "../include/Texture.h"

Texture::Texture(const uint16_t p_width, const uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_pixels(new Color(0, 0, 0, 255))
{
	m_pixelBuffer = new uint32_t[m_width * m_height];
	ClearBuffer();
}

Texture::Texture(std::string path)
{
	
}

Texture::~Texture() 
{
	delete m_pixelBuffer;
	delete m_pixels;
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
	return m_pixels;
}

uint32_t* Texture::GetPixelBuffer()
{
	return m_pixelBuffer;
}

void Texture::ClearBuffer()
{
	SDL_memset(m_pixelBuffer, 0, m_width * m_height * sizeof(uint32_t));
}
