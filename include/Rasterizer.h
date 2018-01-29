#pragma once

#include "IManager.h"
#include "Scene.h"
#include "Texture.h"
#include "Triangle.h"
#include "SharedContext.h"

class Rasterizer : public IManager
{
public:
	Rasterizer(Texture& p_texture, SharedContext& p_sharedContext);
	~Rasterizer();
	void Setup() override;
	void Close() override;
	void RenderScene(Scene* p_pScene);
	void RenderSceneBlinnPhong(Scene* p_pScene);
	void RenderScenePhong(Scene* p_pScene);
	void RenderSceneWireframe(Scene* p_pScene);
	void RenderTexture(Scene* p_pScene);
	void RenderAlphaBlending(Scene* p_pScene);
	void RenderAntialiasing(Scene* p_pScene);
	void RenderZelda(Scene* p_pScene);
	void Update() override;
	void Draw() const;
	void DrawLine(const float p_x1, const float p_y1, const float p_x2, const float p_y2, Color& p_color1, Color& p_color2) const;
	void DrawTriangle(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangleBlinnPhong(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp) const;
	void DrawTrianglePhong(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_light1, Vertex& p_light2, Vertex& p_light3, Toolbox::Vec3& p_lightcomp) const;
	void DrawTriangleWire(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangleTexture(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Image* p_image) const;
	void DrawTriangleAlphaBlending(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Image* p_image, float p_alpha) const;
	void DrawTriangleNoAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangle2XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangle4XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangle8XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangle16XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void DrawTriangleForAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const;
	void ClearBuffer() const;
	Color PhongColor(Vertex& p_position, Toolbox::Vec3& p_normal, Toolbox::Vec3& p_lightcomp, Color& p_color) const;
	Color BlinnPhongColor(Toolbox::Vec3& p_position, Toolbox::Vec3& p_normal, Vertex& p_lightPosition, Toolbox::Vec3& p_lightcomp, Color& p_color) const;

private:
	Texture& m_rtexture;
	SharedContext& m_sharedContext;
	bool m_zBufferOn;
	float* m_zBuffer;
};