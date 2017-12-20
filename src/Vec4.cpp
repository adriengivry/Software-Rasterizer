#include "Vec4.h"


Vec4::Vec4(const Vec3& vec3, float _w)
{
	this->m_x = vec3.m_x;
	this->m_y = vec3.m_y;
	this->m_z = vec3.m_z;
	this->m_w = _w;
}

Vec4::Vec4()
{
	this->m_x = 0;
	this->m_y = 0;
	this->m_z = 0;
	this->m_w = 1;
}

Vec4::~Vec4()
{
}

void Vec4::Homogenize()
{
	this->m_x = this->m_x / this->m_w;
	this->m_y = this->m_y / this->m_w;
	this->m_z = this->m_z / this->m_w;
}
float Vec4::Getmagnitude() const
{
	float mag = sqrtf((this->m_x * this->m_x) + (this->m_y * this->m_y) + (this->m_z * this->m_z));
	return mag;
}
void Vec4::Normalize()
{
	float mag = this->Getmagnitude();
	this->m_x /= mag;
	this->m_y /= mag;
	this->m_z /= mag;
}
Vec4& Vec4::operator+(const Vec4& other)
{
	
	float x = this->m_x + other.m_x;
	float y = this->m_y + other.m_y;
	float z = this->m_z + other.m_z;
	Vec3 temp1(x, y, z);
	Vec4 temp2(temp1, 1);
	return temp2;
}
Vec4& Vec4::operator*(const float& scale)
{
	float x = scale * this->m_x;
	float y = scale *this->m_y;
	float z = scale *this->m_z;
	Vec3 temp1(x, y, z);
	Vec4 temp2(temp1, 1);
	return temp2;
}
