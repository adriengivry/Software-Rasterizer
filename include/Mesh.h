#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Image.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
	static Mesh* CreateCube();
	static Mesh* CreateTextureCube();
    static Mesh* CreateSphere(const int p_latitudeCount,const int p_longitudeCount);
	static Mesh* CreateTriangle();
	static Mesh* CreateZelda();
	static Mesh* CreateWave();
	std::vector<Vertex>& GetVertices();
	std::vector<uint32_t>& GetIndices();

	void SetImage(Image* p_image);
	Image * GetImage() const;
	void SetVertex(const Vertex p_vertex);
	void SetIndex(const uint32_t p_index);
	void SetColor(const float p_r, const float p_g, const float p_b, const float p_a = 255);
private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	Image* m_pImage;
};