#pragma once
#include <cstdint>
#include "Scene.h"
#include "Window.h"

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
	uint8_t selectedVersion = 2;
};

struct SharedContext
{
	Scene* scene = nullptr;
	Window* window = nullptr;

	ApplicationInfos appInfos;
	Actions actions;
};