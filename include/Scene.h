#pragma once
#include <vector>
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();

private:
	std::vector<Entity> m_entities;
};

