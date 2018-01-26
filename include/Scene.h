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
	void InitMeshes(const uint8_t p_rasterizerVersion, const uint8_t p_meshMode);
	void InitEntities(const uint8_t p_rasterizerVersion, const uint8_t p_meshMode);
	void InitLights(const uint8_t p_rasterizerVersion);
	std::map<std::string, Mesh*> meshes;
	std::vector<Entity*> entities;
	std::vector<Light*> lights;
	std::vector<Image*> cubeTextures;
	std::vector<Image*> sphereTextures;
	Image* zeldaImage;
	Image* transparent;
	Image* background;
	Image* waterWave;
};