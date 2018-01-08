#pragma once
#include "Rasterizer.h"

class Display
{
public:
	Display();
	~Display();
	void update();
	void init();
	void initScene();
	void RenderScene();
private:
	Scene* m_pScene;
	Entity** m_pEntity;
	Light* m_pLight;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	Texture* m_prTexture;
	Rasterizer m_pRasterizer;
	float yturn;
};