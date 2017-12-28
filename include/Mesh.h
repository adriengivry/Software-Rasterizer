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

	std::vector<Vertex> GetVertices();
	std::vector<uint32_t> GetIndices();

	void SetVertex(const Vertex p_vertex);
	void SetIndex(const uint32_t p_index);

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
};

