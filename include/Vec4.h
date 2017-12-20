#pragma once
#include "Vec3.h"

struct Vec4
{
	float x;
	float y;
	float z;
	float w;
	Vec4(const Vec3& p_vec3, const float p_w = 1.0f);
	Vec4(const float p_x = 0, const float p_y = 0 , float p_z = 0, float p_w = 1.0f);
	void Homogenize();
	float Getmagnitude() const;
	void Normalize();
	Vec4 operator+(const Vec4& p_other) const;
	Vec4 operator*(const float& p_scale) const;
};

inline Vec4::Vec4(const Vec3& p_vec3, float p_w)
{
	this->x = p_vec3.x;
	this->y = p_vec3.y;
	this->z = p_vec3.z;
	this->w = p_w;
}

inline Vec4::Vec4(const float p_x, const float p_y, float p_z, float p_w)
{
	this->x = p_x;
	this->y = p_y;
	this->z = p_z;
	this->w = p_w;
}

inline void Vec4::Homogenize()
{
	this->x = this->x / this->w;
	this->y = this->y / this->w;
	this->z = this->z / this->w;
}

inline float Vec4::Getmagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

inline void Vec4::Normalize()
{
	this->x /= this->Getmagnitude();
	this->y /= this->Getmagnitude();
	this->z /= this->Getmagnitude();
}

inline Vec4 Vec4::operator+(const Vec4& p_other) const
{

	Vec4 temp2(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z, 1);
	return temp2;
}

inline Vec4 Vec4::operator*(const float& p_scale) const
{
	Vec4 temp2(p_scale * this->x, p_scale * this->y, p_scale * this->z, 1);
	return temp2;
}
