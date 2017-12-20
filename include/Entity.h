#pragma once
#include "Mesh.h"
#include "Mat4.h"

class Entity
{
public:
	Entity();
	~Entity();

private:
	Mesh* m_mesh;
	Mat4 m_transformation;
};

