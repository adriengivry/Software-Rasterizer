#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
	static Mesh* CreateCube();
    static Mesh* CreateSphere(int p_latitudeCount, int p_longitudeCount);
	static Mesh* CreateTriangle();
	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();

	void SetVertex(const Vertex p_vertex);
	void SetIndex(const uint32_t p_index);
	void SetColor(const float p_r, const float p_g, const float p_b, const float p_a = 255);

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	Texture* m_pTexture;
};

