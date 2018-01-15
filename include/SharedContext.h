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
	bool xTurnClockwise;
	bool xTurnCounterClockwise;
	bool yTurnClockwise;
	bool yTurnCounterClockwise;
};

struct LightParams
{
	uint8_t ambiant = 50;
	uint8_t diffuse = 70;
	uint8_t specular = 90;
};

struct ApplicationInfos
{
	bool isRunning = true;
	float lastTime = 0;
	float currentTime = 0;
	float deltaTime = 0;
	uint16_t fpsCounter = 0;
	uint16_t minFps = 65535;
	uint16_t maxFps = 0;
	uint16_t averageFps = 0;
	uint16_t fpsValues[10];
	uint8_t fpsValuesBuffer = 0;
	uint8_t selectedVersion = 1;
	uint8_t selectedLight = AMBIANT;
	LightParams lightParams;
};

struct SharedContext
{
	Scene* scene = nullptr;
	Window* window = nullptr;

	ApplicationInfos appInfos;
	Actions actions;
};