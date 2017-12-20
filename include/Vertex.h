#pragma once
#include "Vec3.h"

struct Vertex
{
	Vec3 position;

    Vertex(const float p_x, const float p_y, const float p_z)
    {
		position.x = p_x;
		position.y = p_y;
		position.z = p_z;
    }
};

