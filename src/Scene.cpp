#include "../include/Scene.h"

Scene::Scene() {}
Scene::~Scene() {}

std::vector<Entity> Scene::GetEntity()
{
	return m_entities;
}
