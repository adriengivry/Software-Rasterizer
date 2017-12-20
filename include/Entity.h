#pragma once
#include "Mesh.h"
#include "Mat4.h"

class Entity
{
public:
	Mesh* mesh;
	Mat4 transformation;
	Entity();
	~Entity();
};

