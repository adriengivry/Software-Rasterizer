#pragma once
#include <vector>
#include "Entity.h"
#include "Light.h"
#include <map>

struct Scene
{
	Scene();
	~Scene();
	void InitMeshes();
	void InitEntities();
	void InitLights();
	std::map<std::string, Mesh*> meshes;
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
};
