#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

Mesh* Mesh::CreateCube()
{
	Mesh* New = new Mesh;
	Vertex p1(-0.5f, +0.5f, 0); 
	Vertex p2(-0.5f, -0.5f, 0);
	Vertex p3(0.5f, -0.5f, 0); 
	Vertex p4(0.5f, +0.5f, 0);
	Vertex p5(-0.5f, 0.5f, 0);
	Vertex p6(-0.5f, -0.5f, 0);
	Vertex p7(0.5f, -0.5f, 0); 
	Vertex p8(0.5f, +0.5f, 0);
	New->vertices.push_back(p1);
	New->vertices.push_back(p2);
	New->vertices.push_back(p3);
	New->vertices.push_back(p4);
	New->vertices.push_back(p5);
	New->vertices.push_back(p6);
	New->vertices.push_back(p7);
	New->vertices.push_back(p8);
	return New;
}
Mesh* Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
	
}
