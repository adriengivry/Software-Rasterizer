#pragma once
#include <cstdint>

struct Color
{
	float r, g, b, a;
	Color(const float p_r, const float p_g, const float p_b, const float p_a)
	{
		this->r = p_r;
		this->g = p_g;
		this->b = p_b;
		this->a = p_a;
	}
	uint32_t CovertTo32();
	Color operator+(const Color& p_color) const;
	Color operator-(const Color& p_color) const;
	Color operator*(const float p_scale) const;
	Color operator/(float p_scale) const;
	Color operator=(const Color& p_color);
};

inline uint32_t Color::CovertTo32()
{
	if (r < 0)
	{
		this->r = 0;
	}
	else if (g < 0)
	{
		this->g = 0;
	}
	else if (b < 0)
	{
		this->b = 0;
	}
	else if (a < 0)
	{
		this->a = 0;
	}
	uint32_t r1 = (uint32_t)(this->r);
	uint32_t g1 = (uint32_t)(this->g);
	uint32_t b1 = (uint32_t)(this->b);
	uint32_t a1 = (uint32_t)(this->a);
	return (b1 << 24) | (g1 << 16) | (r1 << 8) | a1;
}

inline Color Color::operator+(const Color& p_color) const
{
	return Color(this->r + p_color.r, this->g + p_color.g, this->b + p_color.b, this->a + p_color.a);
}
inline Color Color::operator-(const Color& p_color) const
{
	return Color(this->r - p_color.r, this->g - p_color.g, this->b - p_color.b, this->a - p_color.a);
}
inline Color Color::operator*(const float p_scale) const
{
	return Color(p_scale * this->r, p_scale * this->g, p_scale * this->b, p_scale * this->a);
}

inline Color Color::operator/(float p_scale) const
{
	if (p_scale <= 0)
	{
		p_scale = 1;
	}
	return Color(this->r / p_scale, this->g / p_scale, this->b / p_scale, this->a / p_scale);
}

inline Color Color::operator=(const Color & p_color)
{
	this->r = p_color.r;
	this->g = p_color.g;
	this->b = p_color.b;
	this->a = p_color.a;
}
