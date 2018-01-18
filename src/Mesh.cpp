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
	Mesh* Sphere = new Mesh();
	int index = 0;
	for(float latNumber = 0; latNumber <= p_latitudeCount; latNumber++)
	{
		float theta = latNumber * M_PI / p_latitudeCount;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for(float longNumber = 0; longNumber <= p_longitudeCount; longNumber++)
		{
			float phi = longNumber * 2 * M_PI / p_longitudeCount;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			float x = cosPhi * sinTheta;
			float y = cosTheta;
			float z = sinPhi * sinTheta;
			Sphere->GetVertices().push_back(Vertex(x, y, z));
			Sphere->GetVertices()[index].texCoordinate.x = 1 - (longNumber / p_longitudeCount);
			Sphere->GetVertices()[index].texCoordinate.y = 1 - (latNumber / p_latitudeCount);
			Sphere->GetVertices()[index].normal.x = -x;
			Sphere->GetVertices()[index].normal.y = -y;
			Sphere->GetVertices()[index].normal.z = -z;
			index++;
		}
	}
	for(int latNumber = 0; latNumber < p_latitudeCount; latNumber++)
	{
		for(int longNumber = 0; longNumber < p_longitudeCount; longNumber++)
		{
			{
				int first = (latNumber * (p_longitudeCount + 1)) + longNumber;
				int second = first + p_longitudeCount + 1;

				Sphere->GetIndices().push_back(first);
				Sphere->GetIndices().push_back(second);
				Sphere->GetIndices().push_back(first + 1);
				
				Sphere->GetIndices().push_back(second);
				Sphere->GetIndices().push_back(second + 1);
				Sphere->GetIndices().push_back(first + 1);
			}
		}
	}

	for (uint16_t i = 0; i < Sphere->m_vertices.size(); ++i)
	{
		Sphere->m_vertices[i].normal.Normalize();
	}
	return Sphere;
}

Mesh* Mesh::CreateTriangle()
{
	Mesh* Triangle = new Mesh();
	Triangle->m_vertices.push_back(Vertex(sqrt(3), -1, 0));
	Triangle->m_vertices.push_back(Vertex(0, 2, 0));
	Triangle->m_vertices.push_back(Vertex(-sqrt(3), -1, 0));
	Triangle->m_indices.push_back(0);
	Triangle->m_indices.push_back(2);
	Triangle->m_indices.push_back(1);
	return Triangle;
}

Mesh* Mesh::CreateZelda()
{
	Mesh* Triangle = new Mesh();
	Triangle->m_vertices.push_back(Vertex(sqrt(3), -1, 1));
	Triangle->m_vertices.push_back(Vertex(-sqrt(3), -1, 1));
	Triangle->m_vertices.push_back(Vertex(0, 2, 1));
	Triangle->m_indices.push_back(0);
	Triangle->m_indices.push_back(1);
	Triangle->m_indices.push_back(2);

	Triangle->m_vertices.push_back(Vertex(sqrt(3), -1, -1));
	Triangle->m_vertices.push_back(Vertex(-sqrt(3), -1, -1));
	Triangle->m_vertices.push_back(Vertex(0, 2, -1));
	Triangle->m_indices.push_back(3);
	Triangle->m_indices.push_back(4);
	Triangle->m_indices.push_back(5);
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