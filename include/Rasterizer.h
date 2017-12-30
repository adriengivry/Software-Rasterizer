#include "Scene.h"
#include "Texture.h"

class Rasterizer
{
public:
	Rasterizer(Texture& p_texture);
	~Rasterizer();
	void RenderScene(Scene* p_pScene);
	void Init();
	void update();
	void drawLine(float p_x1, float p_y1, float p_x2, float p_y2, Color& p_color1, Color& p_color2);

private:
	Texture& m_rtexture;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
};