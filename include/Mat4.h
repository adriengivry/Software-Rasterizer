#pragma once
#include "Vec4.h"
#include <iostream>

struct Mat4
{
	float m_matrix[4][4];

	Mat4();
	explicit Mat4(Vec4& p_vec4);
	Mat4 operator*(const Mat4& p_other);
	Vec4 operator*(const Vec4& p_other);
	static Mat4 CreatePerspective(float p_fov, float p_aspectRatio, float p_zNear, float p_zFar);
	static Mat4 CreateTranslation(float p_x, float p_y, float p_z);
	static Mat4 CreateView(float p_eyeX, float p_eyeY, float p_eyeZ, float p_lookX, float p_lookY, float p_lookZ, float p_upX, float p_upY, float p_upZ);
	static Mat4 CreateRotation(float p_xAngle, float p_yAngle, float p_zAngle);
	static Mat4 CreateScale(float p_xScale, float p_yScale, float p_zScale);
	static Mat4 CreateFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_zNear, float p_zFar);
	Vec3 transform(Vec3& other);
	static Vec3 ConvertToScreen(const Vec3& p_vector, float p_width, float p_height);
	void SetNull();
	Mat4& Identity();
	void SetIdentity();
	void DisplayData() const;
};

inline Mat4::Mat4(Vec4& p_vec4)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				if (i == 0)
				{
					this->m_matrix[i][j] = p_vec4.x;
				}
				else if (i == 1)
				{
					this->m_matrix[i][j] = p_vec4.y;
				}
				else if (i == 2)
				{
					this->m_matrix[i][j] = p_vec4.z;
				}
				else if (i == 3)
				{
					this->m_matrix[i][j] = p_vec4.w;
				}
			}
		}
	}
}

inline Mat4::Mat4()
{
	SetIdentity();
}

inline Mat4 Mat4::operator*(const Mat4& p_other)
{
	Mat4 toReturn;

	for (uint8_t row = 0; row < 4; ++row)
	{
		for (uint8_t col = 0; col < 4; ++col)
		{
			float value = 0;
			for (uint8_t u = 0; u < 4; ++u)
			{
				value += m_matrix[row][u] * p_other.m_matrix[u][col];
			}
			toReturn.m_matrix[row][col] = value;
		}
	}
	return toReturn;
}

inline Vec4 Mat4::operator*(const Vec4& p_other)
{
	float multVec = 0;
	Vec4 multiply;
	for (int i = 0; i < 4; i++)
	{
		{
			multVec += this->m_matrix[i][0] * p_other.x;
			multVec += this->m_matrix[i][1] * p_other.y;
			multVec += this->m_matrix[i][2] * p_other.z;
			multVec += this->m_matrix[i][3] * p_other.w;
		}
		if (i == 0)
		{
			multiply.x = multVec;
		}
		else if (i == 1)
		{
			multiply.y = multVec;
		}
		else if (i == 2)
		{
			multiply.z = multVec;
		}
		else
		{
			multiply.w = multVec;
		}
		multVec = 0;
	}
	return multiply;
}

inline Mat4 Mat4::CreatePerspective(float p_fov, float p_aspectRatio, float p_zNear, float p_zFar)
{
	
	float tangent = tanf(p_fov / 2 * DEG_TO_RAD);
	float height = p_zNear * tangent;
	float width = height * p_aspectRatio;
	return CreateFrustum(-width, width, -height, height, p_zNear, p_zFar);
}

inline Mat4 Mat4::CreateFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_zNear, float p_zFar)
{
	float maxView, width, height, zRange;
	maxView = 2.0 * p_zNear;
	width = p_right - p_left;
	height = p_top - p_bottom;
	zRange = p_zFar - p_zNear;
	Mat4 Frustum;
	Frustum.m_matrix[0][0] = maxView / width;
	Frustum.m_matrix[1][1] = maxView / height;
	Frustum.m_matrix[2][0] = (p_right + p_left) / width;
	Frustum.m_matrix[2][1] = (p_top + p_bottom) / height;
	Frustum.m_matrix[2][2] = (-p_zFar - p_zNear) / zRange;
	Frustum.m_matrix[2][3] = -1.0f;
	Frustum.m_matrix[3][2] = (-maxView * p_zFar) / zRange;
	Frustum.m_matrix[3][3] = 0.0f;
	return Frustum;
}

inline Mat4 Mat4::CreateTranslation(float p_x, float p_y, float p_z)
{
	Mat4 Translate;
	Translate.m_matrix[0][3] = p_x;
	Translate.m_matrix[1][3] = p_y;
	Translate.m_matrix[2][3] = p_z;
	return Translate;
}

inline Mat4 Mat4::CreateView(float p_eyeX, float p_eyeY, float p_eyeZ, float p_lookX, float p_lookY, float p_lookZ, float p_upX, float p_upY, float p_upZ)
{
	Vec3 eye(p_eyeX, p_eyeY, p_eyeZ);
	Vec3 look(p_lookX, p_lookY, p_lookZ);
	Vec3 up(p_upX, p_upY, p_upZ);
	Vec3 eye_look(eye - look);
	Vec3 n(eye_look / eye_look.GetMagnitude());
	Vec3 UpXn(up.Cross(n));
	Vec3 u(UpXn / UpXn.GetMagnitude());
	Vec3 v(n.Cross(u));
	Mat4 View;
	View.m_matrix[0][0] = u.x;
	View.m_matrix[0][1] = u.y;
	View.m_matrix[0][2] = u.z;
	View.m_matrix[0][3] = -(eye.dot(u));
	View.m_matrix[1][0] = v.x;
	View.m_matrix[1][1] = v.y;
	View.m_matrix[1][2] = v.z;
	View.m_matrix[1][3] = -(eye.dot(v));
	View.m_matrix[2][0] = n.x;
	View.m_matrix[2][1] = n.y;
	View.m_matrix[2][2] = n.z;
	View.m_matrix[2][3] = -(eye.dot(n));
	return View;
}

inline Mat4 Mat4::CreateRotation(float p_xAngle, float p_yAngle, float p_zAngle)
{
	Mat4 xRot, yRot, zRot;
	float xRad = p_xAngle * M_PI / 180.0f;
	float yRad = p_yAngle * M_PI / 180.0f;
	float zRad = p_zAngle * M_PI / 180.0f;

	xRot.m_matrix[1][1] = cos(xRad);
	xRot.m_matrix[1][2] = -sin(xRad);
	xRot.m_matrix[2][1] = sin(xRad);
	xRot.m_matrix[2][2] = cos(xRad);

	yRot.m_matrix[0][0] = cos(yRad);
	yRot.m_matrix[0][2] = -sin(yRad);
	yRot.m_matrix[2][0] = sin(yRad);
	yRot.m_matrix[2][2] = cos(yRad);

	zRot.m_matrix[0][0] = cos(zRad);
	zRot.m_matrix[0][1] = -sin(zRad);
	zRot.m_matrix[1][0] = sin(zRad);
	zRot.m_matrix[1][1] = cos(zRad);

	return (yRot * xRot * zRot);
}

inline Mat4 Mat4::CreateScale(float p_xScale, float p_yScale, float p_zScale)
{
	Mat4 Scale;
	Scale.m_matrix[0][0] = p_xScale;
	Scale.m_matrix[1][1] = p_yScale;
	Scale.m_matrix[2][2] = p_zScale;

	return Scale;
}



inline Vec3 Mat4::transform(Vec3 & other)
{
	return Vec3();
}

inline Vec3 Mat4::ConvertToScreen(const Vec3& p_vector, float p_width, float p_height)
{
	float widthHalf = p_width / 2.0f;
	float heightHalf = p_height / 2.0f;
	return Vec3(((p_vector.x / 5.0f) + 1) * widthHalf, p_height - ((p_vector.y / 5.0f) + 1) * heightHalf, p_vector.z);
}

inline void Mat4::SetNull()
{
	for (uint16_t row = 0; row < 4; ++row)
		for (uint16_t col = 0; col < 4; ++col)
			m_matrix[row][col] = 0;
}

inline Mat4 & Mat4::Identity()
{
	SetIdentity();
	return *this;
}

inline void Mat4::SetIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				this->m_matrix[i][j] = 1;
			else
			{
				this->m_matrix[i][j] = 0;
			}
		}
	}
}

inline void Mat4::DisplayData() const
{
	for (uint16_t row = 0; row < 4; ++row)
	{
		for (uint16_t col = 0; col < 4; ++col)
		{
			std::cout << m_matrix[row][col] << " ";
		}
		std::cout << std::endl;
	}
}
