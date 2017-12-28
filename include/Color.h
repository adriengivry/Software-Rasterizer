#pragma once
#include <cstdint>

struct Color
{
	uint8_t r, g, b, a;
	Color(uint8_t p_r, uint8_t p_g, uint8_t p_b, uint8_t p_a)
	{
		if (p_r > 255)
			p_r = 255;
		else if (p_g > 255)
			p_g = 255;
		else if (p_b > 255)
			p_b = 255;
		else if (p_a > 255)
			p_a = 255;
	
		r = p_r;
		g = p_g;
		b = p_b;
		a = p_a;
	}
	uint32_t CovertTo32() const;
	Color operator+(const Color& p_color) const;
	Color operator-(const Color& p_color) const;
	Color operator*(const uint8_t p_scale) const;
};

inline uint32_t Color::CovertTo32() const
{
	uint32_t r = (uint32_t)(r * 255);
	uint32_t g = (uint32_t)(g * 255);
	uint32_t b = (uint32_t)(b * 255);
	uint32_t a = (uint32_t)(a * 255);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

inline Color Color::operator+(const Color& p_color) const
{
	return Color(r + p_color.r, g + p_color.g, b + p_color.g, a + p_color.a);
}
inline Color Color::operator-(const Color& p_color) const
{
	return Color(r - p_color.r, g - p_color.g, b - p_color.g, a - p_color.a);
}
inline Color Color::operator*(const uint8_t p_scale) const
{
	return Color(p_scale * r, p_scale * g, p_scale * b, p_scale * a);
}