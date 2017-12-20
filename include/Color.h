#pragma once
#include <cstdint>

struct Color
{
	uint8_t r, g, b, a;
	Color(const uint8_t p_r, const uint8_t p_g, const uint8_t p_b, const uint8_t p_a)
	{
		r = p_r;
		g = p_g;
		b = p_b;
		a = p_a;
	}
};