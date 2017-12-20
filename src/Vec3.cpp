#include "Vec3.h"
#include <SDL.h>

Vec3::Vec3(float _x, float _y, float _z)
{
	this->x = _x;
	this->y = _y;
	this->z = _z;
}

Vec3::~Vec3()
{

}

float Vec3::GetMagnitude() const
{
	float mag = sqrtf((this->m_x * this->m_x) + (this->m_y* this->m_y) + (this->m_z * this->m_z));
}

void Vec3::Normalize()
{
	float mag = this->GetMagnitude();
	this->m_x = this->m_x / mag;
	this->m_y = this->m_y / mag;
	this->m_z = this->m_z / mag;
}

Vec3& Vec3::operator+(const Vec3& other)
{
	Vec3 temp(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z);
	return temp;
}

Vec3& Vec3::operator*(const float& scale)
{
	Vec3 temp(scale * this->m_x, scale * this->m_y, scale * this->m_z);
	return temp;
}
