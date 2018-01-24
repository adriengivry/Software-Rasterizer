#pragma once
#include "Color.h"
#include <SDL.h>
#include <string>


class Texture
{
public:
	Texture(const uint16_t p_width, const uint16_t p_height);
	~Texture();

	void SetPixelColor(const uint16_t p_x, const uint16_t p_y, Color& p_color) const;
	Color GetPixelColor(const uint16_t p_x, const uint16_t p_y) const;
	Color CalculatePixelColor(const uint32_t& p_pixel) const;
	uint16_t GetWidth() const;
	uint16_t GetHeight() const;
	Color* GetColor() const;
	void SetColor(Color* p_pColor);
	uint32_t* GetPixelBuffer() const;
	void ClearBuffer() const;

private:
	uint32_t* m_pixelBuffer;
	uint16_t m_width;
	uint16_t m_height;
	Color* m_palette;
};
