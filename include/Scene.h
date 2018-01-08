#pragma once
#include <vector>
#include "Entity.h"
#include "Light.h"
struct Scene
{
	Scene();
	std::vector<Entity*> m_entities;
	std::vector<Light*> m_lights;
};