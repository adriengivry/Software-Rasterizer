#include "../include/Scene.h"

Scene::Scene() = default;

Scene::~Scene()
{
	for (auto entity : entities) delete entity;
	for (auto light : lights) delete light;
	for (auto mesh : meshes) delete mesh.second;
}

void Scene::InitMeshes()
{
	meshes.insert(std::pair<std::string, Mesh*>("CUBE", Mesh::CreateCube()));
	meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
	meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateTriangle()));
}

void Scene::InitEntities()
{
	Entity* cube = new Entity();
	cube->SetMesh(*meshes["CUBE"]);
	cube->SetColor(255, 0, 0);

	Entity* cube2 = new Entity();
	cube2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
	
	Entity* cube3 = new Entity();
	cube3->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);

	Entity* triangle = new Entity();
	triangle->SetMesh(*meshes["TRIANGLE"]);
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
