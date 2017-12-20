#pragma once
#include "Vec3.h"

class Vec4
{
public:
	float m_x;
	float m_y;
	float m_z;
	float m_w;
	Vec4(const Vec3& vec3, float _w = 1.0f);
	Vec4();
	~Vec4();
	void Homogenize();
	float Getmagnitude() const;
	void Normalize();
	Vec4& operator+(const Vec4& other);
	Vec4& operator*(const float& scale);
};

