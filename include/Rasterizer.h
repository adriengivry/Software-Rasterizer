#include "Scene.h"
#include "Texture.h"

class Rasterizer
{
public:
	Rasterizer();
	~Rasterizer();
	void RenderScene(Scene* p_pScene, Texture* p_pTarget);
	void Init(Texture* p_pTarget);
	void update(Texture* p_pTarget);
	void drawLine(float p_x1, float p_y1, float p_x2, float p_y2, uint32_t p_color);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
};