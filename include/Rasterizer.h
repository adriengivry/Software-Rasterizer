#include "Scene.h"
#include "Texture.h"
#include "Triangle.h"
class Rasterizer
{
public:
	Rasterizer(Texture& p_texture, SDL_Renderer& p_renderer, SDL_Texture& p_texture1);
	~Rasterizer();
	void RenderScene(Scene* p_pScene);
	void RenderScene2(Scene* p_pScene);
	void RenderScene3(Scene* p_pScene);
	void RenderScenewire(Scene* p_pScene);
	void update();
	void drawLine(const float p_x1, const float p_y1, const float p_x2, const float p_y2, Color& p_color1, Color& p_color2);
	void drawTriangle(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	void drawTriangle2(Vertex p_v0, Vertex p_v1, Vertex p_v2, Vertex p_lightPosition, Vec3 p_lightcomp);
	void drawTriangle3(Vertex p_v0, Vertex p_v1, Vertex p_v2, Vertex p_light1, Vertex p_light2, Vertex p_light3, Vertex p_lightPosition, Vec3 p_lightcomp);
	void drawTiangleWire(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	void drawTriangleSphere(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	void drawTriangleSpan(Vertex p_v0, Vertex p_v1, Vertex p_v2);
	void BeginDraw();
	void ClearBuffer();
	Color PhongColor(Vertex p_position, Vec3 p_normal, Vertex p_lightPosition, Vec3 p_lightcomp, Color p_color);
	Color BlinnPhongColor(Vertex p_position, Vec3 p_normal, Vertex p_lightPosition, Vec3 p_lightcomp, Color p_color);
	void DrawSpan(const Span& p_span, float p_y);
	void FillTriangle(const Edge& p_edge1, const Edge& p_edge2);

private:
	Texture& m_rtexture;
	SDL_Renderer& m_renderer;
	SDL_Texture& m_texture;
	bool m_wireFrame;
	float* m_zBuffer;
};

namespace Mat3Dto2D
{
	extern Mat4 model;
	extern Mat4 view;
	extern Mat4 projection;
	extern Mat4 SphereModel;
};