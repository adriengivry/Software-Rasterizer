#pragma once
#include <vector>
#include "Entity.h"
#include "Light.h"

struct Scene
{
	Scene();
	~Scene();
	void InitEntities();
	void InitLights();
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
};