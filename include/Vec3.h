#pragma once
#include <math.h>
#include <sdl_stdinc.h>
//#define M_PI 3.1415926535f
#define DEG_TO_RAD 3.1415926535f/180.0f
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

namespace Toolbox
{
	struct Vec3
	{
		float x;
		float y;
		float z;
		explicit Vec3(float p_x = 0, float p_y = 0, float p_z = 0);
		Vec3(const Vec3& p_other);
		float GetMagnitude() const;
		void Normalize();
		float dot(const Vec3& p_other)const;
		Vec3 Cross(const Vec3& p_other)const;
		Vec3 operator+(const Vec3& p_other) const;
		Vec3 operator-(const Vec3& p_other) const;
		Vec3 operator*(const float p_scale) const;
		Vec3 operator/(const float p_scale) const;
		Vec3 operator=(const Vec3& p_other);
		Vec3& operator+=(const Vec3& p_other);
	};

	inline Vec3::Vec3(const float p_x, const float p_y, const float p_z)
	{
		this->x = p_x;
		this->y = p_y;
		this->z = p_z;
	}

	inline Vec3::Vec3(const Vec3 & p_other)
	{
		this->x = p_other.x;
		this->y = p_other.y;
		this->z = p_other.z;
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

	inline float Vec3::dot(const Vec3 & p_other) const
	{
		return (x * p_other.x + y * p_other.y + z * p_other.z);
	}

	inline Vec3 Vec3::Cross(const Vec3 & p_other) const
	{
		return Vec3(this->y * p_other.z - this->z * p_other.y, this->z* p_other.x - this->x * p_other.z, this->x * p_other.y - this->y * p_other.x);
	}

	inline Vec3 Vec3::operator+(const Vec3& p_other) const
	{
		return Vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z);
	}

	inline Vec3 Vec3::operator-(const Vec3 & p_other) const
	{
		return Vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z);
	}

	inline Vec3 Vec3::operator*(const float p_scale) const
	{
		return Vec3(p_scale * this->x, p_scale * this->y, p_scale * this->z);
	}

	inline Vec3 Vec3::operator/(const float p_scale) const
	{
		return Vec3(this->x / p_scale, this->y / p_scale, this->z / p_scale);
	}

	inline Vec3 Vec3::operator=(const Vec3 & p_other)
	{
		this->x = p_other.x;
		this->y = p_other.y;
		this->z = p_other.z;
		return *this;
	}

	inline Vec3 & Vec3::operator+=(const Vec3 & p_other)
	{
		this->x += p_other.x;
		this->y += p_other.y;
		this->z += p_other.z;
		return *this;
	}
}