#pragma once
#include "Color.h"

class Texture
{
private:
	unsigned int width;
	unsigned int height;
	Color* pixels;
public:
	Texture(unsigned int _width, unsigned int _height, unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0, unsigned char _a = 255);
	~Texture();
	void SetPixelColor(unsigned int x, unsigned int y, const Color& c);
};

