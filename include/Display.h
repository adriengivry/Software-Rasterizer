#include "Rasterizer.h"

class Display
{
public:
	Display();
	~Display();
	void update();
	void init();
	void RenderScene(Scene* p_pScene);
	void drawLine();
private:
	Rasterizer* m_pRasterizer;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;
	Texture* m_prTexture;
};