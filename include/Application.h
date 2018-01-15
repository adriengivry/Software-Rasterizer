#pragma once
#include "Rasterizer.h"
#include "UserInterface.h"
#include <numeric>
#include "EventManager.h"

struct CameraParams
{
	float xOffset = 0;
	float zoomOffset = 0;
	float xRotationOffset = 0;
	float yRotationOffset = 0;
};

class Application
{
public:
	Application();
	~Application();
	void Update();
	void Draw();
	void Init();
	void RenderScene();
	void UpdateCamera();
	void UpdateLights();

	SharedContext& GetContext();
private:
	Scene m_scene;
	Texture* m_renderTexture;
	SharedContext m_sharedContext;
	Rasterizer m_rasterizer;
	UserInterface* m_userInterface;
	EventManager* m_eventManager;
	Image* m_image;
	Window m_window;

	CameraParams m_cameraParams;
};
