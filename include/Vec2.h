#include <math.h>
struct Vec2
{
	float x;
	float y;
	explicit Vec2(float p_x = 0, float p_y = 0);
	Vec2(const Vec2& p_other);
	float GetMagnitude() const;
	void Normalize();
	Vec2 operator+(const Vec2& p_other) const;
	Vec2 operator-(const Vec2& p_other) const;
	Vec2 operator*(const float& p_scale) const;
	float operator*(const Vec2& p_other) const;
	
};

inline Vec2::Vec2(const float p_x, const float p_y)
{
	this->x = p_x;
	this->y = p_y;
}

inline Vec2::Vec2(const Vec2 & p_other)
{
	this->x = p_other.x;
	this->y = p_other.y;
}

inline float Vec2::GetMagnitude() const
{
	return sqrtf((this->x * this->x) + (this->y* this->y));
}

inline void Vec2::Normalize()
{
	this->x = this->x / this->GetMagnitude();
	this->y = this->y / this->GetMagnitude();
}

inline Vec2 Vec2::operator+(const Vec2 & p_other) const
{
	return Vec2(this->x + p_other.x, this->y + p_other.y);
}

inline Vec2 Vec2::operator-(const Vec2 & p_other) const
{
	return Vec2(this->x - p_other.x, this->y - p_other.y);
}

inline Vec2 Vec2::operator*(const float & p_scale) const
{
	return Vec2(this->x * p_scale, this->y * p_scale);
}

inline float Vec2::operator*(const Vec2 & p_other) const
{
	return (this->x * p_other.x + this->y * p_other.y);
}