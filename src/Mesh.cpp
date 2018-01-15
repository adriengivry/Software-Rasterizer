#include "../include/Mesh.h"

using namespace Toolbox;

Mesh::Mesh(): m_pImage(nullptr) {}
Mesh::~Mesh() {}

Mesh * Mesh::CreateCube()
{
	Mesh* Cube = new Mesh();
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, -0.5));
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5));
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, -0.5));
	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5));
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5));
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, 0.5));
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5));
	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, 0.5));

	Cube->m_vertices[0].texCoordinate = Vec2(1, 0);
	Cube->m_vertices[1].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[2].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[3].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[4].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[5].texCoordinate = Vec2(1, 0);
	Cube->m_vertices[6].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[7].texCoordinate = Vec2(0, 1);

	Cube->m_indices.push_back(2);
	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(0);

	Cube->m_indices.push_back(2);
	Cube->m_indices.push_back(0);
	Cube->m_indices.push_back(1);

	Cube->m_indices.push_back(6);
	Cube->m_indices.push_back(2);
	Cube->m_indices.push_back(1);

	Cube->m_indices.push_back(6);
	Cube->m_indices.push_back(1);
	Cube->m_indices.push_back(5);

	Cube->m_indices.push_back(7);
	Cube->m_indices.push_back(6);
	Cube->m_indices.push_back(5);

	Cube->m_indices.push_back(7);
	Cube->m_indices.push_back(5);
	Cube->m_indices.push_back(4);

	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(7);
	Cube->m_indices.push_back(4);

	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(4);
	Cube->m_indices.push_back(0);

	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(2);
	Cube->m_indices.push_back(6);

	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(6);
	Cube->m_indices.push_back(7);

	Cube->m_indices.push_back(4);
	Cube->m_indices.push_back(5);
	Cube->m_indices.push_back(1);

	Cube->m_indices.push_back(4);
	Cube->m_indices.push_back(1);
	Cube->m_indices.push_back(0);

	for (uint16_t i = 0; i < Cube->m_indices.size() - 2; i+= 3)
	{
		Vec3 Normal;
		Vec3 p1(Cube->m_vertices[Cube->m_indices[i + 1]].position - Cube->m_vertices[Cube->m_indices[i]].position);
		Vec3 p2(Cube->m_vertices[Cube->m_indices[i + 2]].position - Cube->m_vertices[Cube->m_indices[i]].position);
		Normal = p1.Cross(p2);
		Normal.Normalize();
		Cube->m_vertices[Cube->m_indices[i]].normal = Cube->m_vertices[Cube->m_indices[i]].normal + Vec4(Normal, 0);
		Cube->m_vertices[Cube->m_indices[i + 1]].normal = Cube->m_vertices[Cube->m_indices[i + 1]].normal + Vec4(Normal, 0);
		Cube->m_vertices[Cube->m_indices[i + 2]].normal = Cube->m_vertices[Cube->m_indices[i + 2]].normal + Vec4(Normal, 0);
	}
	
	for (uint16_t i = 0; i < Cube->m_vertices.size(); ++i)
	{
		Cube->m_vertices[i].normal.Normalize();
	}
	return Cube;
}

Mesh* Mesh::CreateTextureCube()
{
	Mesh* Cube = new Mesh();
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, -0.5)); //2 0 
	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5)); //3 1
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, -0.5)); //0 2
	
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, -0.5)); //2   3
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, -0.5)); //0  4
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5)); //1  5
	
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5)); //6     6
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, -0.5)); //2   7
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5)); //1      8

	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5)); //6     9
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5)); //1      10
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, 0.5)); //5    11

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, 0.5)); //7   12
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5)); //6    13
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, 0.5)); //5    14

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, 0.5)); //7   15
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, 0.5)); //5    16
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5)); //4  17

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5)); //3  18
	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, 0.5)); //7   19
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5)); //4  20

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5)); //3  21
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5)); //4  22
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, -0.5)); //0  23

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5)); //3  24
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, -0.5)); //2   25
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5)); //6     26

	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, -0.5)); //3  27
	Cube->m_vertices.push_back(Vertex(0.5, 0.5, 0.5)); //6     28
	Cube->m_vertices.push_back(Vertex(-0.5, 0.5, 0.5)); //7   29

	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5)); //4   30
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, 0.5)); //5    31
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5)); //1      32

	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, 0.5)); //4   33
	Cube->m_vertices.push_back(Vertex(0.5, -0.5, -0.5)); //1      34
	Cube->m_vertices.push_back(Vertex(-0.5, -0.5, -0.5)); //0  35
	
	Cube->m_vertices[0].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[1].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[2].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[3].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[4].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[5].texCoordinate = Vec2(1, 0);

	Cube->m_vertices[6].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[7].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[8].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[9].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[10].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[11].texCoordinate = Vec2(1, 0);

	Cube->m_vertices[12].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[13].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[14].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[15].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[16].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[17].texCoordinate = Vec2(1, 0);

	Cube->m_vertices[18].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[19].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[20].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[21].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[22].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[23].texCoordinate = Vec2(1, 0);

	Cube->m_vertices[24].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[25].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[26].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[27].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[28].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[29].texCoordinate = Vec2(1, 0);

	Cube->m_vertices[30].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[31].texCoordinate = Vec2(0, 1);
	Cube->m_vertices[32].texCoordinate = Vec2(0, 0);

	Cube->m_vertices[33].texCoordinate = Vec2(1, 1);
	Cube->m_vertices[34].texCoordinate = Vec2(0, 0);
	Cube->m_vertices[35].texCoordinate = Vec2(1, 0);


	Cube->m_indices.push_back(0);
	Cube->m_indices.push_back(1);
	Cube->m_indices.push_back(2);

	Cube->m_indices.push_back(3);
	Cube->m_indices.push_back(4);
	Cube->m_indices.push_back(5);

	Cube->m_indices.push_back(6);
	Cube->m_indices.push_back(7);
	Cube->m_indices.push_back(8);

	Cube->m_indices.push_back(9);
	Cube->m_indices.push_back(10);
	Cube->m_indices.push_back(11);

	Cube->m_indices.push_back(12);
	Cube->m_indices.push_back(13);
	Cube->m_indices.push_back(14);

	Cube->m_indices.push_back(15);
	Cube->m_indices.push_back(16);
	Cube->m_indices.push_back(17);

	Cube->m_indices.push_back(18);
	Cube->m_indices.push_back(19);
	Cube->m_indices.push_back(20);

	Cube->m_indices.push_back(21);
	Cube->m_indices.push_back(22);
	Cube->m_indices.push_back(23);

	Cube->m_indices.push_back(24);
	Cube->m_indices.push_back(25);
	Cube->m_indices.push_back(26);

	Cube->m_indices.push_back(27);
	Cube->m_indices.push_back(28);
	Cube->m_indices.push_back(29);

	Cube->m_indices.push_back(30);
	Cube->m_indices.push_back(31);
	Cube->m_indices.push_back(32);

	Cube->m_indices.push_back(33);
	Cube->m_indices.push_back(34);
	Cube->m_indices.push_back(35);
	
	return Cube;
}

Mesh* Mesh::CreateSphere(int p_latitudeCount, int p_longitudeCount)
{
	int i, j, k, l;
	float x, y, z, preXZ;
	int pitch = p_longitudeCount + 1;

	//Calculate angles to be used for X and Y, it depends on the nbr of Lines for Latitudes and Longitudes
	float yAngle = (180.0f / (float)pitch) * DEG_TO_RAD;
	float xAngle = (360.0f / (float)p_latitudeCount) * DEG_TO_RAD;

	Mesh* Sphere = new Mesh();
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

Mesh* Mesh::CreateTriangle()
{
	Mesh* Triangle = new Mesh();
	Triangle->m_vertices.push_back(Vertex(-0.5, -0.5, 0));
	Triangle->m_vertices[0].SetColor(255, 0, 0, 255);
	Triangle->m_vertices.push_back(Vertex(0.5, -0.5, 0));
	Triangle->m_vertices[1].SetColor(0, 255, 0, 255);
	Triangle->m_vertices.push_back(Vertex(0, 0.5, 0));
	Triangle->m_vertices[2].SetColor(0, 0, 255, 255);
	Triangle->m_indices.push_back(0);
	Triangle->m_indices.push_back(1);
	Triangle->m_indices.push_back(2);
	return Triangle;
}

std::vector<Vertex>& Mesh::GetVertices()
{
	return m_vertices;
}

std::vector<uint32_t>& Mesh::GetIndices()
{
	return m_indices;
}

void Mesh::SetImage(Image* p_image)
{
	m_pImage = p_image;
}

Image* Mesh::GetImage()
{
	return m_pImage;
}

void Mesh::SetVertex(const Vertex p_vertex)
{
	m_vertices.push_back(p_vertex);
}

void Mesh::SetIndex(const uint32_t p_index)
{
	m_indices.push_back(p_index);
}

void Mesh::SetColor(const float p_r, const float p_g, const float p_b, const float p_a)
{
	for (auto& i : m_vertices) i.SetColor(p_r, p_g, p_b, p_a);
}