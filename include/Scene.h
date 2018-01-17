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
	void InitMeshes(uint8_t p_rasterizerVersion, uint8_t p_meshMode);
	void InitEntities(uint8_t p_rasterizerVersion, uint8_t p_meshMode);
	void InitLights();
	std::map<std::string, Mesh*> meshes;
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
	std::map<std::string, Image*> textures;
};
