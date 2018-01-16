#include "../include/Scene.h"

Scene::Scene() = default;

Scene::~Scene()
{
	for (auto entity : entities) delete entity;
	for (auto light : lights) delete light;
}

void Scene::InitEntities()
{
	Entity* cube = new Entity();
	cube->SetMesh(*Mesh::CreateCube());
	cube->SetColor(255, 0, 0);

	Entity* cube2 = new Entity();
	cube2->SetMesh(*Mesh::CreateTextureCube());
	
	Entity* cube3 = new Entity();
	cube3->SetMesh(*Mesh::CreateTextureCube());

	Entity* triangle = new Entity();
	triangle->SetMesh(*Mesh::CreateTriangle());
	triangle->SetColor(255, 0, 0);
	entities.push_back(cube);
	entities.push_back(cube2);
	entities.push_back(cube3);
	entities.push_back(triangle);
}

void Scene::InitLights()
{
	lights.push_back(new Light(0, 0, 0));
}
