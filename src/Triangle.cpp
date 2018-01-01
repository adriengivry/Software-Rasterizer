#include "../include/Triangle.h"
Triangle::Triangle(Vertex p_v0, Vertex p_v1, Vertex p_v2) : m_v0(p_v0), m_v1(p_v1), m_v2(p_v2)
{}

Vec3 Triangle::Barycentric(Vertex p_minX, Vertex p_minY, Vertex p_maxX, Vertex p_point)
{
	Vec2 v0(p_maxX.position.x - p_minX.position.x, p_maxX.position.y - p_minX.position.y);
	Vec2 v1(p_minY.position.x - p_minX.position.x, p_minY.position.y - p_minX.position.y);
	Vec2 v2(p_point.position.x - p_minX.position.x, p_point.position.y - p_minX.position.y);

	float Denom = 1.0f / ((v0 * v0) * (v1 * v1) - (v0 * v1) * (v0 * v1));
	float u = ((v1 * v1) * (v0 * v2) - (v0 * v1) * (v1 * v2)) * Denom;
	float v = ((v0 * v0) * (v1 * v2) - (v0 * v1) * (v0 * v2)) * Denom;
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
