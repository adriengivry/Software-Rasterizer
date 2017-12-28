#pragma once
#include <vector>
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Entity> GetEntity();

private:
	std::vector<Entity> m_entities;
};

