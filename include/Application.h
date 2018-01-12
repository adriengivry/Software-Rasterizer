#pragma once
#include "Rasterizer.h"
#include "UserInterface.h"
#include <numeric>
#include "EventManager.h"

class Application
{
public:
	Application();
	~Application();
	void Update();
	void Draw();
	void Init();
	void RenderScene();

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
	float yturn;
};
