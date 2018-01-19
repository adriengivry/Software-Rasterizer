#pragma once
#include <cstdint>
#include "Scene.h"
#include "Window.h"
#include <atomic>

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


enum MESHMODE
{
	CUBE,
	SPHERE
};

struct Actions
{
	bool moveLeft;
	bool moveRight;
	bool moveUp;
	bool moveDown;
	bool zoomIn;
	bool zoomOut;
	bool xTurnClockwise;
	bool xTurnCounterClockwise;
	bool yTurnClockwise;
	bool yTurnCounterClockwise;
	bool zTurnClockwise;
	bool zTurnCounterClockwise;
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

struct MeshParams
{
	float red;
	float green;
	float blue;
	float transparency;
	uint8_t cubeImageID = 0;
	uint8_t sphereImageID = 0;

	MeshParams() { Reset(); }

	void Reset()
	{
		red = 255;
		green = 0;
		blue = 0;
		transparency = 75;
	}
};

struct CameraParams
{
	float xOffset;
	float yOffset;
	float zoomOffset;
	float xRotationOffset;
	float yRotationOffset;
	float zRotationOffset;

	CameraParams() { Reset(); }

	void Reset()
	{
		xOffset = 0;
		yOffset = 0;
		zoomOffset = -6;
		xRotationOffset = 45;
		yRotationOffset = 45;
		zRotationOffset = 0;
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
	MeshParams meshParams;
	CameraParams cameraParams;
	uint8_t selectedAA = NOAA;
	uint16_t polygons = 0;
	uint8_t meshMode = CUBE;

	void Reset()
	{
		selectedLight = AMBIANT;
		selectedAA = NOAA;
		lightParams.Reset();
		meshParams.Reset();
		cameraParams.Reset();
	}
};

struct SharedContext
{
	Scene* scene = nullptr;
	Window* window = nullptr;

	ApplicationInfos appInfos;
	Actions actions;

	void RefreshScene() const
	{
		scene->ClearScene();
		scene->InitMeshes(appInfos.selectedVersion, appInfos.meshMode);
		scene->InitEntities(appInfos.selectedVersion, appInfos.meshMode);
		scene->InitLights();
	}
};