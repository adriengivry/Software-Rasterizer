#pragma once
#include "Vec4.h"
#include <SDL_stdinc.h>
class Mat4
{
public:
	float m_matrix[4][4];
	Mat4(Vec4& vec4);
	Mat4();
	~Mat4();
	Mat4& operator*(const Mat4& other);
	Vec4& operator*(const Vec4& other);
    static Mat4 CreateTransformMatrix(const Vec3& rotation, const Vec3& position, const Vec3& scale);
	static Mat4 CreateTranslationMatrix(const Vec3& translation);
	static Mat4 CreateScaleMatrix(const Vec3& scale);
	static Mat4 CreateXRotationMatrix(float angle);
	static Mat4 CreateYRotationMatrix(float angle);
	static Mat4 CreateZRotationMatrix(float angle);
};

