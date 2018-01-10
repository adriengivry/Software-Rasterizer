#pragma once
#include "Vertex.h"
#include "Vec2.h"
#include <algorithm>

struct AABB
{
	Toolbox::Vec3 minPoint;
	Toolbox::Vec3 maxPoint;
	AABB(const Toolbox::Vec3 p_minPoint,const Toolbox::Vec3 p_maxPoint) : minPoint(p_minPoint), maxPoint(p_maxPoint) {};
};

struct Edge
{
	Color color1, color2;
	float x1, y1, x2, y2;
	Edge(const float p_x1, const float p_y1, const float p_x2, const float p_y2, const Color& p_color1, const Color& p_color2);
};

struct Span
{
	Color color1, color2;
	float x1, x2;
	Span(const float p_x1, const float p_x2, const Color& p_color1, const Color& p_color2);
};



class Triangle
{
public:
	Triangle(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	Toolbox::Vec3 Barycentric(Vertex p_minX, Vertex p_minY, Vertex p_maxX, Vertex p_point);
	AABB getAABB();
	float getArea();
	float CrossProduct(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	Vertex getV0();
	Vertex getV1();
	Vertex getV2();
private:
	Vertex m_v0;
	Vertex m_v1;
	Vertex m_v2;
	Toolbox::Vec2 m_V0;
	Toolbox::Vec2 m_V1;
	float m_d00;
	float m_d11;
	float m_d01;
	float m_d10;
	float m_Denom;
};