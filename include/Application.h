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

	SharedContext& GetContext();
private:
	Scene* m_pScene;
	Entity** m_pEntity;
	Light* m_pLight;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	Texture* m_prTexture;
	SharedContext m_sharedContext;
	Rasterizer m_pRasterizer;
	UserInterface* m_userInterface;
	EventManager* m_eventManager;

	CameraParams m_cameraParams;
};
