#pragma once
#include "Mat4.h"
#include "Color.h"
struct Vertex
{
	Vec3 position;
	Color color;
    Vertex(const float p_x, const float p_y, const float p_z)
    {
		position.x = p_x;
		position.y = p_y;
		position.z = p_z;
    }
	Vertex(const Vec3& p_position)
	{
		position.x = p_position.x;
		position.y = p_position.y;
		position.z = p_position.z;
	}
	void setColor(Color& p_color)
	{
		color = p_color;
	}
	void SetColor(const float p_r,const float p_g,const float p_b,const float p_a)
	{
		color.a = p_a;
		color.r = p_r;
		color.g = p_g;
		color.b = p_b;
	}
	void VertexTransform(Mat4& p_transform)
	{
		Vec4 vector4(position);
		Vec4 vector = p_transform * vector4;
		position.x = (vector.x / (vector.w));
		position.y = (vector.y / (vector.w));
		position.z = vector.z / vector.w;
	}
};

