#pragma once
#include <vector>
#include "Vertex.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
    static Mesh* CreateCube();
    static Mesh* CreateSphere(int p_latitudeCount, int p_longitudeCount);

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
};

