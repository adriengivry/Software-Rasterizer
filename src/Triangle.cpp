#include "../include/Triangle.h"

using namespace Toolbox;

Triangle::Triangle(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) : m_v0(p_v0), m_v1(p_v1), m_v2(p_v2), m_aabb(Vec2(0, 0), Vec2(0, 0))
{
	m_V0 = Vec2(m_v2.position.x - m_v0.position.x, m_v2.position.y - m_v0.position.y);
	m_V1 = Vec2(m_v1.position.x - m_v0.position.x, m_v1.position.y - m_v0.position.y);
	m_d00 = m_V0.x * m_V0.x + m_V0.y * m_V0.y;
	m_d01 = m_V0.x * m_V1.x + m_V0.y * m_V1.y;
	m_d10 = m_V1.x * m_V0.x + m_V1.y * m_V1.y;
	m_d11 = m_V1.x * m_V1.x + m_V1.y * m_V1.y;
	m_Denom = 1.0f / (m_d00 * m_d11 - m_d01 * m_d01);
}
	

Vec3& Triangle::Barycentric(Vertex& p_v0, Vertex& p_point)
{
	const float x = p_point.position.x - p_v0.position.x;
	const float y = p_point.position.y - p_v0.position.y;

	const float d02 = m_V0.x * x + m_V0.y * y;
	const float d12 = m_V1.x * x + m_V1.y * y;
	const float v = (m_d11 * d02 - m_d01 * d12) * m_Denom;
	const float u = (m_d00 * d12 - m_d01 * d02) * m_Denom;

	m_barycentric.x = v;
	m_barycentric.y = u;
	m_barycentric.z = 1.0f - v - u;

	return m_barycentric;
}

AABB& Triangle::GetAABB()
{
	m_aabb.minPoint.x = std::min(std::min(m_v0.position.x, m_v1.position.x), m_v2.position.x);
	m_aabb.minPoint.y = std::min(std::min(m_v0.position.y, m_v1.position.y), m_v2.position.y);

	m_aabb.maxPoint.x = std::max(std::max(m_v0.position.x, m_v1.position.x), m_v2.position.x);
	m_aabb.maxPoint.y = std::max(std::max(m_v0.position.y, m_v1.position.y), m_v2.position.y);

	return m_aabb;
}

float Triangle::GetArea() const
{
	return	  m_v0.position.x * m_v1.position.y
			- m_v1.position.x * m_v0.position.y
			+ m_v1.position.x * m_v2.position.y
			- m_v2.position.x * m_v1.position.y
			+ m_v2.position.x * m_v0.position.y
			- m_v0.position.x * m_v2.position.y;
}

float Triangle::CrossProduct(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2)
{
	return	  (p_v1.position.x - p_v0.position.x)
			* (p_v2.position.y - p_v0.position.y)
			- (p_v1.position.y - p_v0.position.y)
			* (p_v2.position.x - p_v0.position.x);
}

Vertex& Triangle::getV0()
{
	return m_v0;
}

Vertex& Triangle::getV1()
{
	return m_v1;
}

Vertex& Triangle::getV2()
{
	return m_v2;
}

Edge::Edge(const float p_x1, const float p_y1, const float p_x2, const float p_y2, const Color & p_color1, const Color & p_color2)
{
	if (p_y1 < p_y2)
	{
		color1 = p_color1;
		x1 = p_x1;
		y1 = p_y1;
		color2 = p_color2;
		x2 = p_x2;
		y2 = p_y2;
	}
	else
	{
		color1 = p_color2;
		x1 = p_x2;
		y1 = p_y2;
		color2 = p_color1;
		x2 = p_x1;
		y2 = p_y1;
	}
}

Span::Span(const float p_x1, const float p_x2, const Color & p_color1, const Color & p_color2)
{
	if (p_x1 < p_x2)
	{
		color1 = p_color1;
		x1 = p_x1;
		color2 = p_color2;
		x2 = p_x2;
	}
	else
	{
		color1 = p_color2;
		x1 = p_x2;
		color2 = p_color1;
		x2 = p_x1;
	}
}
