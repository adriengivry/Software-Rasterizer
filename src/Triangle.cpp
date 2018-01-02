#include "../include/Triangle.h"
Triangle::Triangle(Vertex p_v0, Vertex p_v1, Vertex p_v2) : m_v0(p_v0), m_v1(p_v1), m_v2(p_v2)
{}

Vec3 Triangle::Barycentric(Vertex p_minX, Vertex p_minY, Vertex p_maxX, Vertex p_point)
{
	Vec2 v0(p_maxX.position.x - p_minX.position.x, p_maxX.position.y - p_minX.position.y);
	Vec2 v1(p_minY.position.x - p_minX.position.x, p_minY.position.y - p_minX.position.y);
	Vec2 v2(p_point.position.x - p_minX.position.x, p_point.position.y - p_minX.position.y);

	float u = ((v1 * v1) * (v0 * v2) - (v0 * v1) * (v1 * v2)) / ((v0 * v0) * (v1 * v1) - (v0 * v1) * (v0 * v1));
	float v = ((v0 * v0) * (v1 * v2) - (v0 * v1) * (v0 * v2)) / ((v0 * v0) * (v1 * v1) - (v0 * v1) * (v0 * v1));
	return Vec3(u, v, 1.0f - (u + v));
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
