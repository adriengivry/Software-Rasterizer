#pragma once
#include "Mat4.h"
#include "Color.h"
struct Vertex
{
	Vec3 position;
	Vec4 normal;
	Color color;
    Vertex(const float p_x, const float p_y, const float p_z)
    {
		position.x = p_x;
		position.y = p_y;
		position.z = p_z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		normal.w = 0;
    }
	Vertex(const Vec3& p_position)
	{
		position.x = p_position.x;
		position.y = p_position.y;
		position.z = p_position.z;
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
		normal.w = 0;
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
	Vertex LightTransform(const Mat4& p_transform)
	{
		this->normal = (p_transform * this->normal);
		normal.Normalize();
		return *this;
	}
	Vertex VertexTransform(const Mat4& p_transform)
	{
		Vec4 vector4 = p_transform * Vec4(position);
		vector4.Homogenize();
		this->position = Vec3(vector4.x, vector4.y, vector4.z);
		return *this;
	}
	Vertex firstTransform(const Mat4& p_transform)
	{
		Vec4 vector4 = p_transform * Vec4(position);
		Vec4 normal4 = p_transform * normal;
		Vertex temp(Vec3(vector4.x, vector4.y, vector4.z));
		normal4.Normalize();
		temp.normal = normal4;
		return temp;
	}
	Vertex operator=(const Vertex& p_other)
	{
		this->position = p_other.position;
		this->normal = p_other.normal;
		this->color = p_other.color;
		return *this;
	}
};

