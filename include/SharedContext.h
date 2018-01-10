#pragma once
#include <cstdint>
#include "Scene.h"
#include "Window.h"

struct SharedContext
{
	bool isRunning = true;
	uint16_t fpsCounter = 0;
	Scene* scene = nullptr;
	Window* window = nullptr;
};
