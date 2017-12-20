#pragma once
#include "Vec4.h"
#include <SDL_stdinc.h>
struct Mat4
{
	float m_matrix[4][4];
	Mat4(Vec4& p_vec4);
	Mat4();
	Mat4 operator*(const Mat4& p_other);
	Vec4 operator*(const Vec4& p_other);
    static Mat4 CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale);
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

inline Mat4 Mat4::operator*(const Mat4& p_other)
{
	float Multsum = 0;
	Mat4 Multiply;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				Multsum = Multsum + this->m_matrix[i][k] * p_other.m_matrix[k][j];
			}
			Multiply.m_matrix[i][j] = Multsum;
		}
	}
	return Multiply;
}

inline Vec4 Mat4::operator*(const Vec4& p_other)
{
	float MultVec = 0;
	Vec4 Multiply;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MultVec = MultVec + this->m_matrix[i][j] * p_other.x;
			MultVec = MultVec + this->m_matrix[i][j] * p_other.y;
			MultVec = MultVec + this->m_matrix[i][j] * p_other.z;
		}
		if (i == 0)
		{
			Multiply.x = MultVec;
		}
		else if (i == 1)
		{
			Multiply.y = MultVec;
		}
		else if (i == 2)
		{
			Multiply.z = MultVec;
		}
		MultVec = 0;
	}
	return Multiply;
}

inline Mat4 Mat4::CreateTransformMatrix(const Vec3& p_rotation, const Vec3& p_position, const Vec3& p_scale)
{
	const float angleX = p_rotation.x * M_PI / 180;
	const float angleY = p_rotation.y * M_PI / 180;
	const float angleZ = p_rotation.z * M_PI / 180;
	Mat4 Transform;
	//set Rotation First
	Transform.m_matrix[0][0] = cos(angleY) * cos(angleZ);
	Transform.m_matrix[0][1] = -cos(angleY) * sin(angleZ);
	Transform.m_matrix[0][2] = s

	//set Translation
	Transform.m_matrix[0][3] = p_position.x;
	Transform.m_matrix[1][3] = p_position.y;
	Transform.m_matrix[2][3] = p_position.z;
	//set Scaling
	Transform.m_matrix[3][0] = p_scale.x;
	Transform.m_matrix[3][1] = p_scale.y;
	Transform.m_matrix[3][2] = p_scale.z;
	return Transform;
}