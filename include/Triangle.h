#include "Vertex.h"
#include "Vec2.h"
#include <algorithm>
struct AABB
{
	Vec3 minPoint;
	Vec3 maxPoint;
	AABB(Vec3 p_minPoint, Vec3 p_maxPoint) : minPoint(p_minPoint), maxPoint(p_maxPoint) {};
};

class Triangle
{
public:
	Triangle(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	Vec3 Barycentric(Vertex p_minX, Vertex p_minY, Vertex p_maxX, Vertex p_point);
	AABB getAABB();
	Vertex getV0();
	Vertex getV1();
	Vertex getV2();

private:
	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;
};