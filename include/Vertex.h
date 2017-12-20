#pragma once
#include "Vec3.h"

struct Vertex
{
	Vec3 position;

    Vertex(const float p_x, const float p_y, const float p_z)
    {
		position.m_x = p_x;
		position.m_y = p_y;
		position.m_z = p_z;
    }
};

