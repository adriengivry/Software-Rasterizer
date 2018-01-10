#pragma once
#include "Vec4.h"
#include <iostream>
#define EPSILON 0.00001f

namespace Toolbox
{
	struct Mat4
	{
		float m_matrix[4][4];

		Mat4();
		Mat4(const Vec4& p_vec4);
		Mat4(const Mat4& p_mat4);
		Mat4 operator*(const Mat4& p_other);
		Vec4 operator*(const Vec4& p_other) const;
		static Mat4 CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar);
		static Mat4 CreateTranslation(const float p_x, const float p_y, const float p_z);
		static Mat4 CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ, const float p_lookX, const float p_lookY, const float p_lookZ, const float p_upX, const float p_upY, const float p_upZ);
		static Mat4 CreateRotation(const float p_xAngle, const float p_yAngle, const float p_zAngle);
		static Mat4 CreateScale(const float p_xScale, const float p_yScale, const float p_zScale);
		static Mat4 CreateFrustum(const float p_left, const float p_right, const float p_bottom, const float p_top, const float p_zNear, const float p_zFar);
		Mat4 CreateInverse();
		Mat4 CreateTranspose();
		static Vec3 ConvertToScreen(const Vec3& p_vector, const float p_width, const float p_height);
		static Vec3 ScreenToView(const Vec3& p_vector, const float p_width, const float p_height);
		void SetNull();
		static Mat4 Identity();
		void SetIdentity();
		float Determinant();
		float GetMinor(float p_m0, float p_m1, float p_m2, float p_m3, float p_m4, float p_m5, float p_m6, float p_m7, float p_m8);
		void DisplayData() const;
	};

	inline Mat4::Mat4(const Vec4& p_vec4)
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

	inline Mat4::Mat4(const Mat4 & p_mat4)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_matrix[i][j] = p_mat4.m_matrix[i][j];
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

	inline Vec4 Mat4::operator*(const Vec4& p_other) const
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
			else if (i == 3)
			{
				multiply.w = multVec;
			}
			multVec = 0;
		}
		return multiply;
	}

	inline Mat4 Mat4::CreatePerspective(const float p_fov, const float p_aspectRatio, const float p_zNear, const float p_zFar)
	{

		float tangent = tanf(p_fov / 2 * DEG_TO_RAD);
		float height = p_zNear * tangent;
		float width = height * p_aspectRatio;
		return CreateFrustum(-width, width, -height, height, p_zNear, p_zFar);
	}

	inline Mat4 Mat4::CreateFrustum(const float p_left, const float p_right, const float p_bottom, const float p_top, const float p_zNear, const float p_zFar)
	{
		float maxView, width, height, zRange;
		maxView = 2.0f * p_zNear;
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

	inline Mat4 Mat4::CreateInverse()
	{
		float cof0 = GetMinor(m_matrix[1][1], m_matrix[2][1], m_matrix[3][1], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]);
		float cof1 = GetMinor(m_matrix[0][1], m_matrix[2][1], m_matrix[3][1], m_matrix[0][2], m_matrix[2][2], m_matrix[3][2], m_matrix[0][3], m_matrix[2][3], m_matrix[3][3]);
		float cof2 = GetMinor(m_matrix[0][1], m_matrix[1][1], m_matrix[3][1], m_matrix[0][2], m_matrix[1][2], m_matrix[3][2], m_matrix[0][3], m_matrix[1][3], m_matrix[3][3]);
		float cof3 = GetMinor(m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);

		float det = m_matrix[0][0] * cof0 - m_matrix[1][0] * cof1 + m_matrix[2][0] * cof2 - m_matrix[3][0] * cof3;
		if (fabs(det) <= EPSILON)
			return this->Identity();

		float cof4 = GetMinor(m_matrix[1][0], m_matrix[2][0], m_matrix[3][0], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]);
		float cof5 = GetMinor(m_matrix[0][0], m_matrix[2][0], m_matrix[3][0], m_matrix[0][2], m_matrix[2][2], m_matrix[3][2], m_matrix[0][3], m_matrix[2][3], m_matrix[3][3]);
		float cof6 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[3][0], m_matrix[0][2], m_matrix[1][2], m_matrix[3][2], m_matrix[0][3], m_matrix[1][3], m_matrix[3][3]);
		float cof7 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);

		float cof8 = GetMinor(m_matrix[1][0], m_matrix[2][0], m_matrix[3][0], m_matrix[1][1], m_matrix[2][1], m_matrix[3][1], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]);
		float cof9 = GetMinor(m_matrix[0][0], m_matrix[2][0], m_matrix[3][0], m_matrix[0][1], m_matrix[2][1], m_matrix[3][1], m_matrix[0][3], m_matrix[2][3], m_matrix[3][3]);
		float cof10 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[3][0], m_matrix[0][1], m_matrix[1][1], m_matrix[3][1], m_matrix[0][3], m_matrix[1][3], m_matrix[3][3]);
		float cof11 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);

		float cof12 = GetMinor(m_matrix[1][0], m_matrix[2][0], m_matrix[3][0], m_matrix[1][1], m_matrix[2][1], m_matrix[3][1], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2]);
		float cof13 = GetMinor(m_matrix[0][0], m_matrix[2][0], m_matrix[3][0], m_matrix[0][1], m_matrix[2][1], m_matrix[3][1], m_matrix[0][2], m_matrix[2][2], m_matrix[3][2]);
		float cof14 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[3][0], m_matrix[0][1], m_matrix[1][1], m_matrix[3][1], m_matrix[0][2], m_matrix[1][2], m_matrix[3][2]);
		float cof15 = GetMinor(m_matrix[0][0], m_matrix[1][0], m_matrix[2][0], m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[0][2], m_matrix[1][2], m_matrix[2][2]);

		float detInv = 1.0f / det;
		Mat4 inverse = *this;

		inverse.m_matrix[0][0] = detInv * cof0;
		inverse.m_matrix[1][0] = -detInv * cof4;
		inverse.m_matrix[2][0] = detInv * cof8;
		inverse.m_matrix[3][0] = -detInv * cof12;
		inverse.m_matrix[0][1] = -detInv * cof1;
		inverse.m_matrix[1][1] = detInv * cof5;
		inverse.m_matrix[2][1] = -detInv * cof9;
		inverse.m_matrix[3][1] = detInv * cof13;
		inverse.m_matrix[0][2] = detInv * cof2;
		inverse.m_matrix[1][2] = -detInv * cof6;
		inverse.m_matrix[2][2] = detInv * cof10;
		inverse.m_matrix[3][2] = -detInv * cof14;
		inverse.m_matrix[0][3] = -detInv * cof3;
		inverse.m_matrix[1][3] = detInv * cof7;
		inverse.m_matrix[2][3] = -detInv * cof11;
		inverse.m_matrix[3][3] = detInv * cof15;

		return inverse;
	}

	inline Mat4 Mat4::CreateTranspose()
	{
		Mat4 Transpose;
		for (uint16_t i = 0; i < 4; i++)
		{
			for (uint16_t j = 0; j < 4; j++)
			{
				Transpose.m_matrix[i][j] = m_matrix[j][i];
			}
		}
		return Transpose;
	}

	inline Mat4 Mat4::CreateTranslation(const float p_x, const float p_y, const float p_z)
	{
		Mat4 Translate;
		Translate.m_matrix[0][3] = p_x;
		Translate.m_matrix[1][3] = p_y;
		Translate.m_matrix[2][3] = p_z;
		return Translate;
	}

	inline Mat4 Mat4::CreateView(const float p_eyeX, const float p_eyeY, const float p_eyeZ, const float p_lookX, const float p_lookY, const float p_lookZ, const float p_upX, const float p_upY, const float p_upZ)
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

	inline Mat4 Mat4::CreateRotation(const float p_xAngle, const float p_yAngle, const float p_zAngle)
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

		return (xRot * yRot * zRot);
	}

	inline Mat4 Mat4::CreateScale(const float p_xScale, const float p_yScale, const float p_zScale)
	{
		Mat4 Scale;
		Scale.m_matrix[0][0] = p_xScale;
		Scale.m_matrix[1][1] = p_yScale;
		Scale.m_matrix[2][2] = p_zScale;

		return Scale;
	}

	inline Vec3 Mat4::ConvertToScreen(const Vec3& p_vector, const float p_width, const float p_height)
	{
		float widthHalf = p_width / 2.0f;
		float heightHalf = p_height / 2.0f;
		return Vec3(((p_vector.x / 5.0f) + 1) * widthHalf, p_height - ((p_vector.y / 5.0f) + 1) * heightHalf, p_vector.z);
	}

	inline Vec3 Mat4::ScreenToView(const Vec3 & p_vector, const float p_width, const float p_height)
	{
		float widthHalf = p_width / 2.0f;
		float heightHalf = p_height / 2.0f;
		return Vec3(((p_vector.x / widthHalf) - 1) * 5.0f, (((p_vector.y - p_height) / -heightHalf) - 1) * 5.0f, p_vector.z);
	}

	inline void Mat4::SetNull()
	{
		for (uint16_t row = 0; row < 4; ++row)
			for (uint16_t col = 0; col < 4; ++col)
				m_matrix[row][col] = 0;
	}

	inline Mat4 Mat4::Identity()
	{
		Mat4 identity;
		return identity;
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

	inline float Mat4::Determinant()
	{
		return m_matrix[0][0] * GetMinor(m_matrix[1][1], m_matrix[2][1], m_matrix[3][1], m_matrix[1][2], m_matrix[2][2], m_matrix[3][2], m_matrix[1][3], m_matrix[2][3], m_matrix[3][3]) -
			m_matrix[1][0] * GetMinor(m_matrix[0][1], m_matrix[2][1], m_matrix[3][1], m_matrix[0][2], m_matrix[2][2], m_matrix[3][2], m_matrix[0][3], m_matrix[2][3], m_matrix[3][3]) +
			m_matrix[2][0] * GetMinor(m_matrix[0][1], m_matrix[1][1], m_matrix[3][1], m_matrix[0][2], m_matrix[1][2], m_matrix[3][2], m_matrix[0][3], m_matrix[1][3], m_matrix[3][3]) -
			m_matrix[3][0] * GetMinor(m_matrix[0][1], m_matrix[1][1], m_matrix[2][1], m_matrix[0][2], m_matrix[1][2], m_matrix[2][2], m_matrix[0][3], m_matrix[1][3], m_matrix[2][3]);
	}

	inline float Mat4::GetMinor(float p_m0, float p_m1, float p_m2, float p_m3, float p_m4, float p_m5, float p_m6, float p_m7, float p_m8)
	{
		return p_m0 * (p_m4 * p_m8 - p_m5 * p_m7) -
			p_m1 * (p_m3 * p_m8 - p_m5 * p_m6) +
			p_m2 * (p_m3 * p_m7 - p_m4 * p_m6);
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
}