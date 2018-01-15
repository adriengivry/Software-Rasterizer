#include "../include/Texture.h"

Texture::Texture(const uint16_t p_width, const uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_palette(nullptr),
	m_rbga(nullptr)
{
	m_pixelBuffer = new uint32_t[m_width * m_height];
	ClearBuffer();
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	m_rbga = SDL_CreateRGBSurface(0, 1, 1, 32,
		rmask, gmask, bmask, amask);
	m_rbga = SDL_ConvertSurfaceFormat(m_rbga, SDL_PIXELFORMAT_RGBA32, 0);
}

Texture::~Texture() 
{
	delete m_pixelBuffer;
	delete m_palette;
	SDL_FreeSurface(m_rbga);
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

Color Texture::CalculatePixelColor(const uint32_t pixel)
{
	uint32_t index = 0;
	uint8_t red, green, blue, alpha;
	SDL_Surface *surface;
	
	index = pixel & m_rbga->format->Rmask;
	index = index >> m_rbga->format->Rshift;
	index = index << m_rbga->format->Rloss;
	red = static_cast<uint8_t>(index);

	index = pixel & m_rbga->format->Gmask;
	index = index >> m_rbga->format->Gshift;
	index = index << m_rbga->format->Gloss;
	green = static_cast<uint8_t>(index);

	index = pixel & m_rbga->format->Bmask;
	index = index >> m_rbga->format->Bshift;
	index = index << m_rbga->format->Bloss;
	blue = static_cast<uint8_t>(index);

	index = pixel & m_rbga->format->Amask;
	index = index >> m_rbga->format->Ashift;
	index = index << m_rbga->format->Aloss;
	alpha = static_cast<uint8_t>(index);

	return Color(red, green, blue, alpha);
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
