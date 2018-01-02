#pragma once
#include <vector>
#include "Entity.h"

struct Scene
{
	Scene();
	std::vector<Entity*> m_entities;
};