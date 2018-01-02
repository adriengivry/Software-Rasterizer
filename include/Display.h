#include "Rasterizer.h"

class Display
{
public:
	Display();
	~Display();
	void update();
	void init();
	void initScene();
	void RenderScene(Scene* p_pScene);
	void drawLine();
private:
	Rasterizer* m_pRasterizer;
	Scene* m_pScene;
	Entity** m_pEntity;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	Texture* m_prTexture;
	float ytransfrom;
};