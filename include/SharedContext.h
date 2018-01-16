#pragma once
#include <cstdint>
#include "Scene.h"
#include "Window.h"

enum LIGHTS
{
	AMBIANT = 1,
	DIFFUSE = 2,
	SPECULAR = 3
};

struct Actions
{
	bool moveLeft;
	bool moveRight;
	bool zoomIn;
	bool zoomOut;
	bool antialiasingZoomIn;
	bool antialiasingZoomOut;
	bool xTurnClockwise;
	bool xTurnCounterClockwise;
	bool yTurnClockwise;
	bool yTurnCounterClockwise;
	bool increaseLight;
	bool decreaseLight;
	bool addRed;
	bool addGreen;
	bool addBlue;
	bool addTransparency;
};

struct LightParams
{
	float ambiant = 50;
	float diffuse = 70;
	float specular = 90;
};

struct CubeParams
{
	float red = 255;
	float green = 0;
	float blue = 0;
	float transparency = 40;
};

struct ApplicationInfos
{
	bool isRunning = true;
	float lastTime = 0;
	float currentTime = 0;
	float deltaTime = 0;
	float secondCubeRotationOffset = 0;
	uint16_t fpsCounter = 0;
	uint16_t minFps = 65535;
	uint16_t maxFps = 0;
	uint16_t averageFps = 0;
	uint16_t fpsValues[10];
	uint8_t fpsValuesBuffer = 0;
	uint8_t selectedVersion = 1;
	uint8_t selectedLight = AMBIANT;
	LightParams lightParams;
	CubeParams cubeParams;

	void Reset()
	{
		selectedVersion = 1;
		selectedLight = AMBIANT;
		lightParams.ambiant = 50;
		lightParams.diffuse = 70;
		lightParams.specular = 90;
		cubeParams.red = 255;
		cubeParams.green = 0;
		cubeParams.blue = 0;
	}
};

struct SharedContext
{
	Scene* scene = nullptr;
	Window* window = nullptr;

	ApplicationInfos appInfos;
	Actions actions;
};