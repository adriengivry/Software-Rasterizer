#include "../include/Mesh.h"

Mesh::Mesh() {}
Mesh::~Mesh() {}

Mesh* Mesh::CreateCube()
{
	uint16_t index, indexA, indexB;
	float x, y, z;
	float yAngle = -90.0f * DEG_TO_RAD;
	float xAngle = 90.0f * DEG_TO_RAD;
	Mesh* Cube = new Mesh();
	if (!Cube->m_vertices.empty())
	{
		Cube->m_vertices.clear();
	}
	else if (!Cube->m_indices.empty())
	{
		Cube->m_indices.clear();
	}

	//Make the first face, Rotation center should be placed at x = 0, y = 0, z = 0
	x = -0.5f;
	y = 0.5f;
	z = 0.5f;
	for (index = 0; index < 4; index++)
	{
		if (index >= 1)
		{
			x = (x * cos(yAngle) + x * sin(yAngle));
			z = (z * -sin(yAngle) + z * cos(yAngle));
		}
		Cube->m_vertices.push_back(Vertex(x, y, z));
		Cube->m_vertices.push_back(Vertex(x, y * cos(xAngle) + y * -sin(xAngle), z * sin(xAngle) + z * cos(xAngle)));
	}
	//Calculate Index
	//draw sides first
	for (index = 0; index < 8; index++)
	{
		indexA = (index == 7) ? -1 : index;
		indexB = (index == 6) ? -2 : index;
		indexB = (index == 7) ? -1 : index;
		Cube->m_indices.push_back(index);
		Cube->m_indices.push_back(indexA + 1);
		Cube->m_indices.push_back(indexB + 2);
	}
	//draw bases
	for (index = 0; index < 2; index++)
	{
		//top/bottom TriangleA
		Cube->m_indices.push_back(index);
		Cube->m_indices.push_back(index + 2);
		Cube->m_indices.push_back(index + 4);

		//Top/bottom TriangleB
		Cube->m_indices.push_back(index + 4);
		Cube->m_indices.push_back(index + 6);
		Cube->m_indices.push_back(index);
	}
	return Cube;
}

Mesh* Mesh::CreateSphere(int p_latitudeCount, int p_longitudeCount)
{
	uint16_t i, j, k, l;
	float x, y, z, preXZ;
	uint16_t pitch = p_longitudeCount + 1;

	//Calculate angles to be used for X and Y, it depends on the nbr of Lines for Latitudes and Longitudes
	float yAngle = (180.0f / (float)pitch) * DEG_TO_RAD;
	float xAngle = (360.0f / (float)p_latitudeCount) * DEG_TO_RAD;

	Mesh* Sphere = new Mesh();
	if (!Sphere->m_vertices.empty())
	{
		Sphere->m_vertices.clear();
	}
	else if (!Sphere->m_indices.empty())
	{
		Sphere->m_indices.clear();
	}

	//It's easier to calculate a sphere from top to bottom.
	for (i = 0; i <= pitch; i++)
	{
		preXZ = sin((float)i * yAngle);
		if (preXZ < 0)
		{
			preXZ = -preXZ;
		}
		y = cos((float)i * yAngle);
		for (j = 0; j < p_latitudeCount; j++)
		{
			x = preXZ * cos((float)j * xAngle);
			z = preXZ * sin((float)j * xAngle);
			Sphere->m_vertices.push_back(Vertex(x, y, z));
		}
	}
	//Calculate indices
	//we can draw square(2 triangles) faces first or triangle on the top/bottom first.

	uint16_t lastVertice = Sphere->m_vertices.size() - 1;
	uint16_t bottomTriangles = p_latitudeCount * (p_longitudeCount - 1);
	//Triangles for Top/bottom
	for (i = 0; i < p_latitudeCount; i++)
	{
		j = (i == p_latitudeCount - 1) ? -1 : i;
		//top triangles
		Sphere->m_indices.push_back(0);
		Sphere->m_indices.push_back(j + 2);
		Sphere->m_indices.push_back(i + 1);

		//bottom triangles
		Sphere->m_indices.push_back(lastVertice);
		Sphere->m_indices.push_back(i + 1 + bottomTriangles);
		Sphere->m_indices.push_back(j + 2 + bottomTriangles);
	}
	//Square faces in the middle
	for (i = 1; i < p_longitudeCount; i++)
	{
		for (j = 0; j < p_latitudeCount; j++)
		{
			k = i * p_latitudeCount + j;
			l = (j == p_latitudeCount - 1) ? k - p_latitudeCount : k;
			//first Triangle
			Sphere->m_indices.push_back(k + 1 - p_latitudeCount);
			Sphere->m_indices.push_back(l + 2 - p_latitudeCount);
			Sphere->m_indices.push_back(k + 1);
			//second Triangle
			Sphere->m_indices.push_back(l + 2 - p_latitudeCount);
			Sphere->m_indices.push_back(k + 1);
			Sphere->m_indices.push_back(l + 2);
		}
	}
	return Sphere;
}

std::vector<Vertex> Mesh::GetVertices()
{
	return m_vertices;
}

std::vector<uint32_t> Mesh::GetIndices()
{
	return m_indices;
}

void Mesh::SetVertex(const Vertex p_vertex)
{
	m_vertices.push_back(p_vertex);
}

void Mesh::SetIndex(const uint32_t p_index)
{
	m_indices.push_back(p_index);
}