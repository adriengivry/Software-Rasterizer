#include "Mesh.h"

Mesh::Mesh() {}

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
	newMesh->vertices.push_back(p1);
	newMesh->vertices.push_back(p2);
	newMesh->vertices.push_back(p3);
	newMesh->vertices.push_back(p4);
	newMesh->vertices.push_back(p5);
	newMesh->vertices.push_back(p6);
	newMesh->vertices.push_back(p7);
	newMesh->vertices.push_back(p8);
	return newMesh;
}
Mesh* Mesh::CreateSphere(int latitudeCount, int longitudeCount) {}
