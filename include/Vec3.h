#pragma once
#include <xutility>
#include <cmath>

struct Vec3
{
	float x;
	float y;
	float z;
	explicit Vec3(float _x = 0, float _y = 0, float _z = 0);
	~Vec3();
	float GetMagnitude() const;
	void Normalize();
	Vec3& operator+(const Vec3& other);
	Vec3& operator*(const float& scale);
};

