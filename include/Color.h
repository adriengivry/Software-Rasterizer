#pragma once
#include <cstdint>

struct Color
{
	float r, g, b, a;

	explicit Color(const float p_r = 0, const float p_g = 0, const float p_b = 0, const float p_a = 255);
	uint32_t CovertTo32();
	Color operator+(const Color& p_color) const;
	Color operator-(const Color& p_color) const;
	Color operator*(const float p_scale) const;
	Color operator/(float p_scale) const;
	Color& operator=(const Color& p_color);
	bool operator==(const Color& p_color) const;
	void Set(const float p_r = 0, const float p_g = 0, const float p_b = 0, const float p_a = 255);
};

inline Color::Color(const float p_r, const float p_g, const float p_b, const float p_a)
{
	Set(p_r, p_g, p_b, p_a);
}

inline uint32_t Color::CovertTo32()
{
	if (r < 0)
	{
		this->r = 0.0f;
	}
	if (g < 0)
	{
		this->g = 0.0f;
	}
	if (b < 0)
	{
		this->b = 0.0f;
	}
	if (a < 0)
	{
		this->a = 0.0f;
	}

	if (r >= 254.99f)
	{
		this->r = 254.99f;
	}
	if (g >= 254.99f)
	{
		this->g = 254.99f;
	}
	if (b >= 254.99f)
	{
		this->b = 254.99f;
	}
	if (a >= 254.99f)
	{
		this->a = 254.99f;
	}
	
	const uint32_t r1 = static_cast<uint32_t>(this->r);
	const uint32_t g1 = static_cast<uint32_t>(this->g);
	const uint32_t b1 = static_cast<uint32_t>(this->b);
	const uint32_t a1 = static_cast<uint32_t>(this->a);
	return (b1 << 24) | (g1 << 16) | (r1 << 8) | a1;
}

inline Color Color::operator+(const Color& p_color) const
{
	Color temp;
	temp.r = this->r + p_color.r;

	temp.g = this->g + p_color.g;
	
	temp.b = this->b + p_color.b;

	temp.a = 254.99f;
	return temp;
}
inline Color Color::operator-(const Color& p_color) const
{
	Color temp;
	temp.r = this->r - p_color.r;

	temp.g = this->g - p_color.g;
	
	temp.b = this->b - p_color.b;


	temp.a = 254.99f;
	return temp;
}
inline Color Color::operator*(const float p_scale) const
{
	Color temp;
	temp.r = this->r * p_scale;
	

	temp.g = this->g * p_scale;


	temp.b = this->b * p_scale;

	temp.a = 254.99f;
	return temp;
}

inline Color Color::operator/(float p_scale) const
{
	if (p_scale <= 0)
	{
		p_scale = 1;
	}
	Color temp;
	temp.r = this->r / p_scale;


	temp.g = this->g / p_scale;
	
	temp.b = this->b / p_scale;
	
	temp.a = 254.99f;
	return temp;
}

inline Color& Color::operator=(const Color & p_color)
{
	this->r = p_color.r;
	this->g = p_color.g;
	this->b = p_color.b;
	this->a = p_color.a;
	return *this;
}

inline bool Color::operator==(const Color & p_color) const
{	
	bool flag = false;
	if (this->r == p_color.r && this->g == p_color.g && this->b == p_color.b && this->a == p_color.a)
	{
		flag = true;
	}
	return flag;
}

inline void Color::Set(const float p_r, const float p_g, const float p_b, const float p_a)
{
	this->r = p_r;
	this->g = p_g;
	this->b = p_b;
	this->a = p_a;
}
