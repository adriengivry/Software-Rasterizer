#pragma once
#include <cmath>

struct Vec3
{
	float x;
	float y;
	float z;
	explicit Vec3(float p_x = 0, float p_y = 0, float p_z = 0);
	float GetMagnitude() const;
	void Normalize();
	Vec3 operator+(const Vec3& p_other) const;
	Vec3 operator*(const float& p_scale) const;
};

inline Vec3::Vec3(float p_x, float p_y, float p_z)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
}

inline float Vec3::GetMagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y* this->y) + (this->z * this->z));
}

inline void Vec3::Normalize()
{
	this->x = this->x / this->GetMagnitude();
	this->y = this->y / this->GetMagnitude();
	this->z = this->z / this->GetMagnitude();
}

inline Vec3 Vec3::operator+(const Vec3& p_other) const
{
	return Vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z);
}

inline Vec3 Vec3::operator*(const float& p_scale) const
{
	return Vec3(p_scale * this->x, p_scale * this->y, p_scale * this->z);
}
