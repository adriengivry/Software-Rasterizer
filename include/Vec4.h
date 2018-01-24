#pragma once
#include "Vec3.h"

namespace Toolbox
{
	struct Vec4
	{
		float x;
		float y;
		float z;
		float w;
		explicit Vec4(const Vec3& p_vec3, const float p_w = 1.0f);
		explicit Vec4(const float p_x = 0, const float p_y = 0, float p_z = 0, float p_w = 1.0f);
		void Homogenize();
		float Getmagnitude() const;
		void Normalize();
		Vec4 Cross(const Vec4& p_other) const;
		Vec4 operator+(const Vec4& p_other) const;
		float operator*(const Vec4& p_other) const;
		Vec4 operator*(const float p_scale) const;
		Vec4& operator=(const Vec4& p_other);
		Vec4& operator/=(const float p_scale);
	};

	inline Vec4::Vec4(const Vec3& p_vec3, const float p_w)
	{
		this->x = p_vec3.x;
		this->y = p_vec3.y;
		this->z = p_vec3.z;
		this->w = p_w;
	}

	inline Vec4::Vec4(const float p_x, const float p_y, const float p_z, const float p_w)
	{
		this->x = p_x;
		this->y = p_y;
		this->z = p_z;
		this->w = p_w;
	}

	inline void Vec4::Homogenize()
	{
		if (this->w != 0)
		{
			this->x = this->x / this->w;
			this->y = this->y / this->w;
			this->z = this->z / this->w;
		}
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

	inline Vec4 Vec4::Cross(const Vec4 & p_other) const
	{
		return Vec4(this->y * p_other.z - this->z * p_other.y, this->z * p_other.x - this->x * p_other.z, this->x * p_other.y - this->y * p_other.x, this->w);
	}

	inline Vec4 Vec4::operator+(const Vec4& p_other) const
	{
		return Vec4(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z, this->z + p_other.z);
	}

	inline float Vec4::operator*(const Vec4 & p_other) const
	{
		return (this->x * p_other.x + this->y * p_other.y + this->z * p_other.z);
	}

	inline Vec4 Vec4::operator*(const float p_scale) const
	{
		return Vec4(p_scale * this->x, p_scale * this->y, p_scale * this->z, this->w * p_scale);
	}

	inline Vec4& Vec4::operator=(const Vec4 & p_other)
	{
		this->x = p_other.x;
		this->y = p_other.y;
		this->z = p_other.z;
		this->w = p_other.w;
		return *this;
	}

	inline Vec4& Vec4::operator/=(const float p_scale)
	{
		x /= p_scale;
		y /= p_scale;
		z /= p_scale;
		w /= p_scale;
		return *this;
	}
}