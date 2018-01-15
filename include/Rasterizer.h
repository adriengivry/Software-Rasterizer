#include "Scene.h"
#include "Texture.h"
#include "Triangle.h"
#include "SharedContext.h"

class Rasterizer
{
public:
	Rasterizer(Texture& p_texture, SharedContext& p_sharedContext);
	~Rasterizer();
	void RenderScene(Scene* p_pScene);
	void RenderSceneBlinnPhong(Scene* p_pScene);
	void RenderScenePhong(Scene* p_pScene);
	void RenderSceneWireframe(Scene* p_pScene);
	void RenderTexture(Scene* p_pScene);
	void RenderAlphaBlending(Scene* p_pScene);
	void Update();
	void Draw();
	void DrawLine(const float p_x1, const float p_y1, const float p_x2, const float p_y2, Color& p_color1, Color& p_color2);
	void DrawTriangle(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2);
	void DrawTriangle2(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp);
	void DrawTriangle3(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_light1, Vertex& p_light2, Vertex& p_light3, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp);
	void DrawTiangleWire(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2);
	void DrawTriangleTexture(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Image* p_image);
	void DrawTriangleAlphaBlending(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2);
	void ClearBuffer();
	Color PhongColor(Vertex& p_position, Toolbox::Vec3& p_normal, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp, Color& p_color);
	Color BlinnPhongColor(Vertex& p_position, Toolbox::Vec3& p_normal, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp, Color& p_color);
	void DrawSpan(const Span& p_span, float p_y);
	void FillTriangle(const Edge& p_edge1, const Edge& p_edge2);

private:
	Texture& m_rtexture;
	SharedContext& m_sharedContext;
	bool m_wireFrame;
	float* m_zBuffer;
};