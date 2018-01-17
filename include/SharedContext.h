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
enum AASELECTION
{
	NOAA,
	AA2X,
	AA4X,
	AA8X,
	AA16X
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
	bool changeAAValue;
	bool showHelp;
};

struct LightParams
{
	float ambiant;
	float diffuse;
	float specular;

	LightParams() { Reset(); }

	void Reset()
	{
		ambiant = 50;
		diffuse = 70;
		specular = 90;
	}
};

struct CubeParams
{
	float red;
	float green;
	float blue;
	float transparency;

	CubeParams() { Reset(); }

	void Reset()
	{
		red = 255;
		green = 0;
		blue = 0;
		transparency = 40;
	}
};

struct CameraParams
{
	float xOffset;
	float zoomOffset;
	float antialiasingOffset;
	float xRotationOffset;
	float yRotationOffset;

	CameraParams() { Reset(); }

	void Reset()
	{
		xOffset = 0;
		zoomOffset = 0;
		antialiasingOffset = 0;
		xRotationOffset = 45;
		yRotationOffset = 45;
	}
};

struct ApplicationInfos
{
	bool isRunning = true;
	bool showInterface = true;
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
	CameraParams cameraParams;
	uint8_t selectedAA = NOAA;

	void Reset()
	{
		selectedLight = AMBIANT;
		selectedAA = NOAA;
		lightParams.Reset();
		cubeParams.Reset();
		cameraParams.Reset();
	}
};

struct SharedContext
{
	Scene* scene = nullptr;
	Window* window = nullptr;

	ApplicationInfos appInfos;
	Actions actions;
};