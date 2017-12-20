#include "Scene.h"



Scene::Scene()
{}


Scene::~Scene()
{
	for(int i = 0; i < this->entities.size(); i++)
	{
		this->entities.pop_back();
	}
}
