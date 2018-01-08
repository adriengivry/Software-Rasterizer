#include "../include/Triangle.h"
Triangle::Triangle(Vertex p_v0, Vertex p_v1, Vertex p_v2) : m_v0(p_v0), m_v1(p_v1), m_v2(p_v2)
{
	m_V0 = Vec2(m_v2.position.x - m_v0.position.x, m_v2.position.y - m_v0.position.y);
	m_V1 = Vec2(m_v1.position.x - m_v0.position.x, m_v1.position.y - m_v0.position.y);
	m_d00 = m_V0 * m_V0;
	m_d01 = m_V0 * m_V1;
	m_d10 = m_V1 * m_V0;
	m_d11 = m_V1 * m_V1;
	m_Denom = 1.0f / (m_d00 * m_d11 - m_d01 * m_d01);
}
	

Vec3 Triangle::Barycentric(Vertex p_v0, Vertex p_v1, Vertex p_v2, Vertex p_point)
{
	Vec2 V2(p_point.position.x - p_v0.position.x, p_point.position.y - p_v0.position.y);
	float d02 = (m_V0 * V2);
	float d12 = (m_V1 * V2);
	float v = (m_d11 * d02 - m_d01 * d12) * m_Denom;
	float u = (m_d00 * d12 - m_d01 * d02) * m_Denom;
	return Vec3(v, u, 1.0f - (v + u));
}

AABB Triangle::getAABB()
{
	Vec3 min(
		std::min(std::min(m_v0.position.x, m_v1.position.x), m_v2.position.x),
		std::min(std::min(m_v0.position.y, m_v1.position.y), m_v2.position.y),
		std::min(std::min(m_v0.position.z, m_v1.position.z), m_v2.position.z)
	);

	Vec3 max(
		std::max(std::max(m_v0.position.x, m_v1.position.x), m_v2.position.x),
		std::max(std::max(m_v0.position.y, m_v1.position.y), m_v2.position.y),
		std::max(std::max(m_v0.position.z, m_v1.position.z), m_v2.position.z)
	);
	return AABB(min, max);
}

float Triangle::getArea()
{
	return (m_v0.position.x * m_v1.position.y) - (m_v1.position.x * m_v0.position.y) + (m_v1.position.x * m_v2.position.y) - (m_v2.position.x * m_v1.position.y) + (m_v2.position.x * m_v0.position.y) - (m_v0.position.x * m_v2.position.y);
}

float Triangle::CrossProduct(Vertex p_v0, Vertex p_v1, Vertex p_v2)
{
	return (p_v1.position.x - p_v0.position.x) * (p_v2.position.y - p_v0.position.y) - (p_v1.position.y - p_v0.position.y) * (p_v2.position.x - p_v0.position.x);
}

Vertex Triangle::getV0()
{
	return m_v0;
}

Vertex Triangle::getV1()
{
	return m_v1;
}

Vertex Triangle::getV2()
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
