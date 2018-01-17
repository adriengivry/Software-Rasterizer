#pragma once
#include <vector>
#include "Entity.h"
#include "Light.h"
#include <map>

struct Scene
{
	Scene();
	~Scene();
	void ClearScene();
	void InitMeshes(uint8_t p_rasterizerVersion);
	void InitEntities(uint8_t p_rasterizerVersion);
	void InitLights();
	std::map<std::string, Mesh*> meshes;
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
	std::vector<Image*> textures;
};
