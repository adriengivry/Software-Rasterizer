#pragma once
#include "Mesh.h"
#include "Mat4.h"

class Entity
{
public:
	Entity();
	~Entity();

	Mesh* GetMesh();
	Toolbox::Mat4& GetMatrix();

	void SetMesh(const Mesh& p_mesh);
	void SetMatrix(const Toolbox::Mat4& p_matrix);
private:
	Mesh* m_mesh;
	Toolbox::Mat4 m_transformation;
};

