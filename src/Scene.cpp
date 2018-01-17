#include "../include/Scene.h"
#include "SharedContext.h"

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

void Scene::InitMeshes(const uint8_t p_rasterizerVersion, uint8_t p_meshMode)
{
	if (p_rasterizerVersion >= 1 && p_rasterizerVersion <= 4)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE", Mesh::CreateCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(20, 20)));
	}
	else if (p_rasterizerVersion == 5)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(20, 20)));

		textures.push_back(new Image("../assets/texture.png")); 

	}
	else if (p_rasterizerVersion == 6)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(20, 20)));

		textures.push_back(new Image("../assets/texture.png"));
		textures.push_back(new Image("../assets/texture2.png"));

	}
	else if (p_rasterizerVersion == 7)
	{
		meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateTriangle()));
	}
}

void Scene::InitEntities(uint8_t p_rasterizerVersion, uint8_t p_meshMode)
{
	if (p_rasterizerVersion >= 1 && p_rasterizerVersion <= 4)
	{
		Entity* entity = new Entity();

		if (p_meshMode == CUBE)
			entity->SetMesh(*meshes["CUBE"]);
		else if (p_meshMode == SPHERE)
			entity->SetMesh(*meshes["SPHERE"]);

		entity->SetColor(255, 0, 0);
		entities.push_back(entity);
	}
	else if (p_rasterizerVersion == 5)
	{
		Entity* entity = new Entity();

		if (p_meshMode == CUBE)
			entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		else if (p_meshMode == SPHERE)
			entity->SetMesh(*meshes["SPHERE"]);

		entity->GetMesh()->SetImage(textures[0]);
		entities.push_back(entity);
	}
	else if (p_rasterizerVersion == 6)
	{
		Entity* entity = new Entity();

		if (p_meshMode == CUBE)
			entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		else if (p_meshMode == SPHERE)
			entity->SetMesh(*meshes["SPHERE"]);

		entity->GetMesh()->SetImage(textures[1]);
		entity->SetAlpha(1.f);
		entities.push_back(entity);

		Entity* entity2 = new Entity();

		if (p_meshMode == CUBE)
			entity2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		else if (p_meshMode == SPHERE)
			entity2->SetMesh(*meshes["SPHERE"]);

		entity2->GetMesh()->SetImage(textures[0]);
		entity2->SetAlpha(0.4f);
		entities.push_back(entity2);
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
