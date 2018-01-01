#include "Scene.h"
#include "Texture.h"
#include "Triangle.h"
class Rasterizer
{
public:
	Rasterizer(Texture& p_texture, SDL_Renderer& p_renderer, SDL_Texture& p_texture1);
	~Rasterizer();
	void RenderScene(Scene* p_pScene);
	void update();
	void drawLine(const float p_x1, const float p_y1, const float p_x2, const float p_y2, Color& p_color1, Color& p_color2);
	void drawTriangle(Vertex p_v0, Vertex p_v1, Vertex p_v2);
private:
	Texture& m_rtexture;
	SDL_Renderer& m_renderer;
	SDL_Texture& m_texture;
	bool m_wireFrame;
};