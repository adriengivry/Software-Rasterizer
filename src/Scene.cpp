#include "../include/Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	ClearScene();
}

void Scene::ClearScene()
{
	for (auto entity : entities) delete entity;
	entities.clear();

	for (auto light : lights) delete light;
	lights.clear();

	for (auto mesh : meshes) delete mesh.second;
	meshes.clear();

	for (auto texture : textures) delete texture;
	textures.clear();
}

void Scene::InitMeshes(const uint8_t p_rasterizerVersion)
{
	if (p_rasterizerVersion >= 1 && p_rasterizerVersion <= 4)
	{
		meshes.insert(std::pair<std::string, Mesh*>("CUBE", Mesh::CreateCube()));
	}
	else if (p_rasterizerVersion == 5)
	{
		meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		textures.push_back(new Image("../assets/texture.png"));	

	}
	else if (p_rasterizerVersion == 6)
	{
		meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		textures.push_back(new Image("../assets/texture.png"));
		textures.push_back(new Image("../assets/texture2.png"));

	}
	else if (p_rasterizerVersion == 7)
	{
		meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateTriangle()));
	}
}

void Scene::InitEntities(uint8_t p_rasterizerVersion)
{
	if (p_rasterizerVersion >= 1 && p_rasterizerVersion <= 4)
	{
		Entity* cube = new Entity();
		cube->SetMesh(*meshes["CUBE"]);
		cube->SetColor(255, 0, 0);
		entities.push_back(cube);
	}
	else if (p_rasterizerVersion == 5)
	{
		Entity* cube = new Entity();
		cube->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		cube->GetMesh()->SetImage(textures[0]);
		entities.push_back(cube);
	}
	else if (p_rasterizerVersion == 6)
	{
		Entity* cube = new Entity();
		cube->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		cube->GetMesh()->SetImage(textures[1]);
		cube->SetAlpha(1.f);
		entities.push_back(cube);

		Entity* cube2 = new Entity();
		cube2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		cube2->GetMesh()->SetImage(textures[0]);
		cube2->SetAlpha(0.4f);
		entities.push_back(cube2);
	}
	else if (p_rasterizerVersion == 7)
	{
		Entity* triangle = new Entity();
		triangle->SetMesh(*meshes["TRIANGLE"]);
		triangle->SetColor(255, 0, 0);
		entities.push_back(triangle);
	}	
}

void Scene::InitLights()
{
	lights.push_back(new Light(0, 0, 0));
}
