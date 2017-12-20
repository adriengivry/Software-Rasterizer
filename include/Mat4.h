#pragma once
#include "Vec4.h"
#include <SDL_stdinc.h>
#include <iostream>

struct Mat4
{
	float m_matrix[4][4];

	Mat4();
	explicit Mat4(Vec4& p_vec4);
	Mat4 operator*(const Mat4& p_other);
	Vec4 operator*(const Vec4& p_other);
    static Mat4 CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale);
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
	float multVec = 0;
	Vec4 multiply;
	for (int i = 0; i < 4; i++)
	{
		{
			multVec = multVec + this->m_matrix[i][0] * p_other.x;
			multVec = multVec + this->m_matrix[i][1] * p_other.y;
			multVec = multVec + this->m_matrix[i][2] * p_other.z;
			multVec = multVec + this->m_matrix[i][3] * p_other.w;
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
		else if(i == 3)
		{
			multiply.w = multVec;
		}
		multVec = 0;
	}
	return multiply;
}

inline Mat4 Mat4::CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale)
{
	const float angleX = p_rotation.x * M_PI / 180;
	const float angleY = p_rotation.y * M_PI / 180;
	const float angleZ = p_rotation.z * M_PI / 180;
	Mat4 transform;
	//set Rotation First
	transform.m_matrix[0][0] = cos(angleY) * cos(angleZ);
	transform.m_matrix[0][1] = -cos(angleY) * sin(angleZ);
	transform.m_matrix[0][2] = sin(angleY);
	
	transform.m_matrix[1][0] = sin(angleX) * sin(angleY) * sin(angleZ) + cos(angleX) * sin(angleZ);
	transform.m_matrix[1][1] = -sin(angleX) * sin(angleY) * sin(angleZ) + cos(angleX) * cos(angleZ);
	transform.m_matrix[1][2] = -sin(angleX) * cos(angleY);

	transform.m_matrix[2][0] = -cos(angleX) * sin(angleY) * cos(angleZ) + sin(angleX) * sin(angleZ);
	transform.m_matrix[2][1] = cos(angleX) * sin(angleY) * sin(angleZ) + sin(angleX) * cos(angleZ);
	transform.m_matrix[2][2] = cos(angleX) * cos(angleY);

	//set Translation
	transform.m_matrix[0][3] = p_position.x;
	transform.m_matrix[1][3] = p_position.y;
	transform.m_matrix[2][3] = p_position.z;
	//set Scaling
	transform.m_matrix[3][0] = p_scale.x;
	transform.m_matrix[3][1] = p_scale.y;
	transform.m_matrix[3][2] = p_scale.z;

	return transform;
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
