#include "Texture.h"

Texture::Texture(unsigned _width, unsigned _height, unsigned char _r, unsigned char _g, unsigned char _b,
	unsigned char _a) : pixels {new Color(_r, _g, _b, _a)}, width{_width}, height{_height}
{};

Texture::~Texture()
{}

void Texture::SetPixelColor(unsigned x, unsigned y, const Color& c)
{
	this->width = x;
	this->height = y;
	*this->pixels = c;
}
