#pragma once
#include <xutility>
#include <cmath>

class Vec3
{
public:
	float m_x;
	float m_y;
	float m_z;
	Vec3(float _x, float _y, float _z);
	~Vec3();
	float GetMagnitude() const;
	void Normalize();
	Vec3& operator+(const Vec3& other);
	Vec3& operator*(const float& scale);
};

