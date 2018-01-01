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
    static Mat4 CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale);
	static Vec3 ConvertToScreen(const Vec3& p_vector, float p_width, float p_height);
	void SetNull();
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
	float multVecX = 0;
	float multVecY = 0;
	float multVecZ = 0;
	float multVecW = 0;
	Vec4 multiply;
	for (int i = 0; i < 4; i++)
	{
		{
			multVecX = multVecX + this->m_matrix[i][0] * p_other.x;
			multVecY = multVecY + this->m_matrix[i][1] * p_other.y;
			multVecZ = multVecZ + this->m_matrix[i][2] * p_other.z;
			multVecW = multVecW + this->m_matrix[i][3] * p_other.w;
		}
		if (i == 3)
		{
			multiply.x = multVecX;
			multiply.y = multVecY;
			multiply.z = multVecZ;
			multiply.w = multVecW;
		}
	}
	return multiply;
}

inline Mat4 Mat4::CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale)
{
	const float angleX = p_rotation.x * M_PI / 180;
	const float angleY = p_rotation.y * M_PI / 180;
	const float angleZ = p_rotation.z * M_PI / 180;
	Mat4 transform;
	//set Rotation/Scaling First
	transform.m_matrix[0][0] = p_scale.x * (cos(angleY) * cos(angleZ) + sin(angleY) * sin(angleX) * sin(angleZ));
	transform.m_matrix[0][1] = p_scale.y * (-cos(angleY) * sin(angleZ) + sin(angleY) * sin(angleX) * cos(angleZ));
	transform.m_matrix[0][2] = p_scale.z * (sin(angleY) * cos(angleX));

	transform.m_matrix[1][0] = p_scale.x * (cos(angleX) * cos(angleZ));
	transform.m_matrix[1][1] = p_scale.y * (cos(angleX) * cos(angleZ));
	transform.m_matrix[1][2] = p_scale.z * (-sin(angleX));

	transform.m_matrix[2][0] = p_scale.x * (-sin(angleY) * cos(angleZ) + cos(angleY) * sin(angleX) * sin(angleZ));
	transform.m_matrix[2][1] = p_scale.y * (sin(angleY) * sin(angleZ) + cos(angleY) * sin(angleX) * cos(angleZ));
	transform.m_matrix[2][2] = p_scale.z * (cos(angleY) * cos(angleX));

	//set Translation
	transform.m_matrix[0][3] = p_position.x;
	transform.m_matrix[1][3] = p_position.y;
	transform.m_matrix[2][3] = p_position.z;

	return transform;
}

inline Vec3 Mat4::ConvertToScreen(const Vec3& p_vector, float p_width, float p_height)
{
	float widthHalf = p_width / 2.0f;
	float heightHalf = p_height / 2.0f;
	Vec3 converted(((p_vector.x / 5.0f) + 1) * widthHalf, p_height - ((p_vector.y / 5.0f) + 1) * heightHalf, p_vector.z);
	return converted;
}

inline void Mat4::SetNull()
{
	for (uint16_t row = 0; row < 4; ++row)
		for (uint16_t col = 0; col < 4; ++col)
			m_matrix[row][col] = 0;
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
