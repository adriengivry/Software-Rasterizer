#include "../include/Texture.h"

Texture::Texture(const uint16_t p_width, const uint16_t p_height) :
	m_width(p_width),
	m_height(p_height),
	m_paletteWidth(0),
	m_paletteHeight(0),
	m_palette(nullptr)
{
	m_pixelBuffer = new uint32_t[m_width * m_height];
	ClearBuffer();
}

Texture::Texture(std::string p_path)
{
	SDL_Surface * imgLoader = nullptr;
	SDL_Surface * rgbaImage = nullptr;
	imgLoader = IMG_Load(p_path.c_str());
	rgbaImage = SDL_ConvertSurfaceFormat(imgLoader, SDL_PIXELFORMAT_RGBA32, 0);
	m_paletteWidth = rgbaImage->w;
	m_paletteHeight = rgbaImage->h;
	m_palette = new Color[m_paletteWidth * m_paletteHeight];
	uint32_t* pixels = static_cast<uint32_t *>(rgbaImage->pixels);
	uint8_t r, g, b, a;
	for(int y = 0; y < m_paletteHeight; ++y)
	{
		for(int x = 0; x < m_paletteWidth; ++x)
		{
			SDL_GetRGBA(pixels[x + y * m_paletteWidth],
				rgbaImage->format, &r, &g, &b, &a);

			m_palette[x + y * m_paletteWidth].r = r;
			m_palette[x + y * m_paletteWidth].g = g;
			m_palette[x + y * m_paletteWidth].b = b;
			m_palette[x + y * m_paletteWidth].a = a;
		}
	}
	delete rgbaImage;
	delete imgLoader;
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

uint16_t Texture::GetWidth()
{
	return m_width;
}

uint16_t Texture::GetHeight()
{
	return m_height;
}

uint16_t Texture::GetPaletteWidth()
{
	return m_paletteWidth;
}

uint16_t Texture::GetPaletteHeight()
{
	return m_paletteHeight;
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
