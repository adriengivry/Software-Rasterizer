#include "../include/Scene.h"
#include "SharedContext.h"
#include <string>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

Scene::Scene()
{
	std::string path = "../assets/textures/cube";
	for (auto & p : fs::directory_iterator(path))
		cubeTextures.push_back(new Image(p.path().string()));

	path = "../assets/textures/sphere";
	for (auto & p : fs::directory_iterator(path))
		sphereTextures.push_back(new Image(p.path().string()));

	zeldaImage = new Image("../assets/textures/zelda/logo.png");
	transparent = new Image("../assets/textures/zelda/transparent.png");
	background = new Image("../assets/textures/zelda/background.png");
}

Scene::~Scene()
{
	ClearScene();

	for (auto texture : cubeTextures)
		delete texture;

	for (auto texture : sphereTextures)
		delete texture;

	delete zeldaImage;	
}

void Scene::ClearScene()
{
	for (auto entity : entities) delete entity;
	entities.clear();

	for (auto light : lights) delete light;
	lights.clear();

	for (auto mesh : meshes) delete mesh.second;
	meshes.clear();
}

void Scene::InitMeshes(const uint8_t p_rasterizerVersion, const uint8_t p_meshMode)
{
	if ((p_rasterizerVersion >= 1 && p_rasterizerVersion <= 2) || p_rasterizerVersion == 4 || p_rasterizerVersion == 8)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE", Mesh::CreateCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(40, 40)));
	}
	else if (p_rasterizerVersion == 3)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE", Mesh::CreateCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(40, 40)));
	}
	else if (p_rasterizerVersion == 5)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		else if (p_meshMode == SPHERE)
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(40, 40)));
	}
	else if (p_rasterizerVersion == 6)
	{
		if (p_meshMode == CUBE)
			meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
		else if (p_meshMode == SPHERE)
		{
			meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
			meshes.insert(std::pair<std::string, Mesh*>("SPHERE", Mesh::CreateSphere(20, 20)));
		}
	}
	else if (p_rasterizerVersion == 7)
	{
		meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateTriangle()));
	}
	else if (p_rasterizerVersion == 0)
	{
		meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateZelda()));
		meshes.insert(std::pair<std::string, Mesh*>("CUBE_WITH_TEXTURE", Mesh::CreateTextureCube()));
	}
}

void Scene::InitEntities(const uint8_t p_rasterizerVersion,const uint8_t p_meshMode)
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
		{
			entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
			entity->GetMesh()->SetImage(cubeTextures[0]);
		}
		else if (p_meshMode == SPHERE)
		{
			entity->SetMesh(*meshes["SPHERE"]);
			entity->GetMesh()->SetImage(sphereTextures[0]);
		}

		
		entities.push_back(entity);
	}
	else if (p_rasterizerVersion == 6)
	{
		Entity* entity = new Entity();
		entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		entity->GetMesh()->SetImage(cubeTextures[0]);
		entity->SetAlpha(1.f);
		entities.push_back(entity);

		Entity* entity2 = new Entity();

		if (p_meshMode == CUBE)
		{
			entity2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
			entity2->GetMesh()->SetImage(cubeTextures[0]);
		}
		else if (p_meshMode == SPHERE)
		{
			entity2->SetMesh(*meshes["SPHERE"]);
			entity2->GetMesh()->SetImage(sphereTextures[0]);
		}

		
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
	else if (p_rasterizerVersion == 0)
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
			Entity* triangle = new Entity();
			triangle->SetMesh(*meshes["TRIANGLE"]);
			triangle->SetColor(204, 153, 0);
			entities.push_back(triangle);
		}

		Entity* rectangle = new Entity();
		rectangle->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		rectangle->SetColor(0, 255, 0);
		rectangle->GetMesh()->SetImage(transparent);
		entities.push_back(rectangle);

		Entity* rectangle2 = new Entity();
		rectangle2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		rectangle2->SetColor(0, 255, 0);
		rectangle2->GetMesh()->SetImage(transparent);
		entities.push_back(rectangle2);
	}
	else if (p_rasterizerVersion == 8)
	{
		Entity* entity = new Entity();

		if (p_meshMode == CUBE)
			entity->SetMesh(*meshes["CUBE"]);
		else if (p_meshMode == SPHERE)
			entity->SetMesh(*meshes["SPHERE"]);

		entity->SetColor(255, 0, 0);
		entities.push_back(entity);
	}
}

void Scene::InitLights()
{
	lights.push_back(new Light(0, 0, 0));
}
