#include "Mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}

Mesh* Mesh::CreateCube()
{
	Mesh* newMesh = new Mesh;
	const Vertex p1(-0.5f, +0.5f, 0); 
	const Vertex p2(-0.5f, -0.5f, 0);
	const Vertex p3(0.5f, -0.5f, 0);
	const Vertex p4(0.5f, +0.5f, 0);
	const Vertex p5(-0.5f, 0.5f, 0);
	const Vertex p6(-0.5f, -0.5f, 0);
	const Vertex p7(0.5f, -0.5f, 0);
	const Vertex p8(0.5f, +0.5f, 0);
	newMesh->m_vertices.push_back(p1);
	newMesh->m_vertices.push_back(p2);
	newMesh->m_vertices.push_back(p3);
	newMesh->m_vertices.push_back(p4);
	newMesh->m_vertices.push_back(p5);
	newMesh->m_vertices.push_back(p6);
	newMesh->m_vertices.push_back(p7);
	newMesh->m_vertices.push_back(p8);
	return newMesh;
}

Mesh* Mesh::CreateSphere(int p_latitudeCount, int p_longitudeCount)
{
	// TODO: Create Sphere method
	return nullptr;
}
