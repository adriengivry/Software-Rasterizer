#include "../include/Scene.h"
#include "SharedContext.h"

Scene::Scene()
{
	textures.insert(std::pair<std::string, Image*>("BOX", new Image("../assets/box.png")));
	textures.insert(std::pair<std::string, Image*>("BIRD", new Image("../assets/bird.png")));
	textures.insert(std::pair<std::string, Image*>("ROCK", new Image("../assets/rock.png")));
	textures.insert(std::pair<std::string, Image*>("WATER", new Image("../assets/water.png")));
	textures.insert(std::pair<std::string, Image*>("EARTH", new Image("../assets/earth.png")));
	textures.insert(std::pair<std::string, Image*>("BRICK", new Image("../assets/brick.png")));
	textures.insert(std::pair<std::string, Image*>("REALISTIC_BRICK", new Image("../assets/realistic_brick.png")));
	textures.insert(std::pair<std::string, Image*>("DIRT", new Image("../assets/dirt.png")));
}

Scene::~Scene()
{
	for (auto pair : textures)
		delete pair.second;

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
}

void Scene::InitMeshes(const uint8_t p_rasterizerVersion, uint8_t p_meshMode)
{
	if (p_rasterizerVersion >= 1 && p_rasterizerVersion <= 2 || p_rasterizerVersion == 4)
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
	else if (p_rasterizerVersion == 8)
	{
		meshes.insert(std::pair<std::string, Mesh*>("TRIANGLE", Mesh::CreateZelda()));
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
		{
			entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
			entity->GetMesh()->SetImage(textures["ROCK"]);
		}
		else if (p_meshMode == SPHERE)
		{
			entity->SetMesh(*meshes["SPHERE"]);
			entity->GetMesh()->SetImage(textures["ROCK"]);
		}

		
		entities.push_back(entity);
	}
	else if (p_rasterizerVersion == 6)
	{
		Entity* entity = new Entity();
		entity->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
		entity->GetMesh()->SetImage(textures["BOX"]);
		entity->SetAlpha(1.f);
		entities.push_back(entity);

		Entity* entity2 = new Entity();

		if (p_meshMode == CUBE)
		{
			entity2->SetMesh(*meshes["CUBE_WITH_TEXTURE"]);
			entity2->GetMesh()->SetImage(textures["ROCK"]);
		}
		else if (p_meshMode == SPHERE)
		{
			entity2->SetMesh(*meshes["SPHERE"]);
			entity2->GetMesh()->SetImage(textures["ROCK"]);
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
	else if (p_rasterizerVersion == 8)
	{
		for (uint8_t i = 0; i < 3; ++i)
		{
			Entity* triangle = new Entity();
			triangle->SetMesh(*meshes["TRIANGLE"]);
			triangle->SetColor(204, 153, 0);
			entities.push_back(triangle);
		}
	}
}

void Scene::InitLights()
{
	lights.push_back(new Light(0, 0, 0));
}
