#include "../include/Rasterizer.h"

using namespace Toolbox;

Rasterizer::Rasterizer(Texture& p_texture, SharedContext& p_sharedContext) :
	m_rtexture(p_texture),
	m_sharedContext(p_sharedContext),
	m_zBufferOn(false),
	m_zBuffer(new float[m_rtexture.GetWidth() * m_rtexture.GetHeight()])
{
	Rasterizer::Setup();
}

Rasterizer::~Rasterizer()
{
	Rasterizer::Close();
}

void Rasterizer::Setup()
{
	for (uint32_t i = 0; i < m_rtexture.GetWidth() * m_rtexture.GetHeight() - 1; ++i)
		m_zBuffer[i] = std::numeric_limits<float>::max();
}

void Rasterizer::Close()
{
	delete[] m_zBuffer;
}

void Rasterizer::RenderScene(Scene * p_pScene)
{
	m_zBufferOn = true;
	switch (m_sharedContext.appInfos.selectedAA)
	{
	case NOAA:
		for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
		{
			const Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
			const Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
			for (int i = 0; i < p_pScene->entities[0]->GetMesh()->GetIndices().size(); i += 3)
			{
				Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
				Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
				Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
				v0.VertexTransform(positionMatrix);
				v1.VertexTransform(positionMatrix);
				v2.VertexTransform(positionMatrix);
				DrawTriangle(v0, v1, v2);
			}
		}
	break;
	
	case AA8X:
		for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
		{
			const Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
			const Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
			for (int i = 0; i < p_pScene->entities[0]->GetMesh()->GetIndices().size(); i += 3)
			{
				Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
				Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
				Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
				v0.VertexTransform(positionMatrix);
				v1.VertexTransform(positionMatrix);
				v2.VertexTransform(positionMatrix);
				DrawTriangle(v0, v1, v2);
			}

			for (int i = 0; i < p_pScene->entities[0]->GetMesh()->GetIndices().size(); i += 3)
			{
				Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
				Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
				Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
				v0.VertexTransform(positionMatrix);
				v1.VertexTransform(positionMatrix);
				v2.VertexTransform(positionMatrix);
				DrawTriangleForAntialiasing(v0, v1, v2);
			}
		}
		break;

	default: break;
	}
}

void Rasterizer::RenderSceneBlinnPhong(Scene * p_pScene)
{
	m_zBufferOn = true;
	Vertex lightposition = p_pScene->lights[0]->GetPosition();
	Vec3 Lightcomp(p_pScene->lights[0]->GetAmbient(), p_pScene->lights[0]->GetDiffuse(), p_pScene->lights[0]->GetSpecular());
	lightposition.VertexTransform(Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f));
	
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 projection = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Mat4 normalMatrixTrans = normalMatrix.CreateInverse();
		normalMatrixTrans = normalMatrixTrans.CreateTranspose();
		for (int i = 0; i < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
			v0.VertexTransform(projection);
			v1.VertexTransform(projection);
			v2.VertexTransform(projection);
			v0.NormalTransform(normalMatrixTrans);
			v1.NormalTransform(normalMatrixTrans);
			v2.NormalTransform(normalMatrixTrans);

			DrawTriangleBlinnPhong(v0, v1, v2, lightposition, Lightcomp);
		}
	}
}

void Rasterizer::RenderScenePhong(Scene * p_pScene)
{
	m_zBufferOn = true;
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 projection1 = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Mat4 normalMatrixTrans = normalMatrix.CreateTranspose();
		normalMatrixTrans = normalMatrixTrans.CreateInverse();
		Vec3 Lightcomp(p_pScene->lights[0]->GetAmbient(), p_pScene->lights[0]->GetDiffuse(), p_pScene->lights[0]->GetSpecular());
		for (int i = 0; i < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
			Vertex light1 = v0.FirstTransform(normalMatrix, normalMatrixTrans);
			Vertex light2 = v1.FirstTransform(normalMatrix, normalMatrixTrans);
			Vertex light3 = v2.FirstTransform(normalMatrix, normalMatrixTrans);
			v0.VertexTransform(projection1);
			v1.VertexTransform(projection1);
			v2.VertexTransform(projection1);
			DrawTrianglePhong(v0, v1, v2, light1, light2, light3, Lightcomp);
		}
	}
}
void Rasterizer::RenderSceneWireframe(Scene * p_pScene)
{
	m_zBufferOn = false;
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		const Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		for (int i = 0; i < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
			v0.VertexTransform(positionMatrix);
			v1.VertexTransform(positionMatrix);
			v2.VertexTransform(positionMatrix);
			DrawTriangleWire(v0, v1, v2);
		}
	}
}

void Rasterizer::RenderTexture(Scene* p_pScene)
{
	m_zBufferOn = false;
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		const Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		for (int i = 0; i < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);

			v0.VertexTransform(positionMatrix);
			v1.VertexTransform(positionMatrix);
			v2.VertexTransform(positionMatrix);
			DrawTriangleTexture(v0, v1, v2, p_pScene->entities[entityID]->GetMesh()->GetImage());
		}
	}
}

void Rasterizer::RenderAlphaBlending(Scene* p_pScene)
{
	m_zBufferOn = false;
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		const Mat4 ModelProjection = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * p_pScene->entities[entityID]->GetMatrix();

		for (int j = 0; j < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; j += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[j]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[j + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[j + 2]]);
			v0.VertexTransform(ModelProjection);
			v1.VertexTransform(ModelProjection);
			v2.VertexTransform(ModelProjection);
			DrawTriangleAlphaBlending(v0, v1, v2, p_pScene->entities[entityID]->GetMesh()->GetImage(), p_pScene->entities[entityID]->GetAlpha());
		}
	}
}

void Rasterizer::RenderAntialiasing(Scene* p_pScene)
{
	m_zBufferOn = false;
	for (uint8_t entityID = 0; entityID < m_sharedContext.scene->entities.size(); ++entityID)
	{
		const Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 modelProjection = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[0]]);
		Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[1]]);
		Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[2]]);
		v0.VertexTransform(modelProjection);
		v1.VertexTransform(modelProjection);
		v2.VertexTransform(modelProjection);
		switch (m_sharedContext.appInfos.selectedAA)
		{
		case NOAA: DrawTriangleNoAntialiasing(v0, v1, v2); break;

		case AA2X: DrawTriangle2XAntialiasing(v0, v1, v2); break;

		case AA4X: DrawTriangle4XAntialiasing(v0, v1, v2); break;

		case AA8X: DrawTriangle8XAntialiasing(v0, v1, v2); break;

		case AA16X: DrawTriangle16XAntialiasing(v0, v1, v2); break;

		default: break;
		}
	}
}

void Rasterizer::RenderZelda(Scene* p_pScene)
{
	m_zBufferOn = true;

	{
		const Mat4 normalMatrix = p_pScene->entities[4]->GetMatrix();
		const Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		for (int i = 0; i < p_pScene->entities[4]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[4]->GetMesh()->GetVertices()[p_pScene->entities[4]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[4]->GetMesh()->GetVertices()[p_pScene->entities[4]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[4]->GetMesh()->GetVertices()[p_pScene->entities[4]->GetMesh()->GetIndices()[i + 2]]);

			v0.VertexTransform(positionMatrix);
			v1.VertexTransform(positionMatrix);
			v2.VertexTransform(positionMatrix);
			DrawTriangleTexture(v0, v1, v2, p_pScene->entities[4]->GetMesh()->GetImage());
		}
	}

	Vertex lightposition = p_pScene->lights[0]->GetPosition();
	Vec3 Lightcomp(1, 1, 1);
	lightposition.VertexTransform(Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f));

	for (int8_t entityID = 0; entityID < 4; ++entityID)
	{
		Mat4 normalMatrix = p_pScene->entities[entityID]->GetMatrix();
		const Mat4 projection = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Mat4 normalMatrixTrans = normalMatrix.CreateInverse();
		normalMatrixTrans = normalMatrixTrans.CreateTranspose();
		for (int i = 0; i < p_pScene->entities[entityID]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->entities[entityID]->GetMesh()->GetVertices()[p_pScene->entities[entityID]->GetMesh()->GetIndices()[i + 2]]);
			v0.VertexTransform(projection);
			v1.VertexTransform(projection);
			v2.VertexTransform(projection);
			v0.NormalTransform(normalMatrixTrans);
			v1.NormalTransform(normalMatrixTrans);
			v2.NormalTransform(normalMatrixTrans);
			if (entityID > 2)
				DrawTriangleTexture(v0, v1, v2, p_pScene->entities[entityID]->GetMesh()->GetImage());
			else
				DrawTriangleBlinnPhong(v0, v1, v2, lightposition, Lightcomp);
		}
	}
}

void Rasterizer::Update()
{
	SDL_UpdateTexture(m_sharedContext.window->GetTexture(), nullptr, m_rtexture.GetPixelBuffer(), m_rtexture.GetWidth() * sizeof(uint32_t));
	m_rtexture.ClearBuffer();
	if (m_zBufferOn)
	{
		for (int i = m_rtexture.GetWidth() * m_rtexture.GetHeight(); i--;)
			m_zBuffer[i] = std::numeric_limits<float>::digits10;
	}
}

void Rasterizer::Draw() const
{
	SDL_RenderCopy(m_sharedContext.window->GetRenderer(), m_sharedContext.window->GetTexture(), nullptr, nullptr);
}

void Rasterizer::DrawLine(const float p_x1, const float p_y1, const float p_x2, const float p_y2, Color& p_color1, Color& p_color2) const
{
	const float dx = p_x2 - p_x1;
	const float dy = p_y2 - p_y1;
	const float dx1 = fabs(p_x2 - p_x1);
	const float dy1 = fabs(p_y2 - p_y1);
	float index = 0;

	if (dx == 0.0f && dy == 0.0f)
	{
		m_rtexture.SetPixelColor(int(p_x1), int(p_y1), p_color1);
		return;
	}
	
	if (fabs(dx) > fabs(dy))
	{
		float xMin, xMax;
		const float slope = dy / dx;

		if (p_x1 < p_x2)
		{
			xMin = p_x1;
			xMax = p_x2;
		}
		else
		{
			xMin = p_x2;
			xMax = p_x1;
		}
		
		for (float x = xMin; x <= xMax; ++x)
		{
			const float y = p_y1 + ((x - p_x1) * slope);
				if (xMin == p_x1)
				{
					const Color color = p_color1 * ((dx1 - index) / dx1);
					const Color color1 = p_color2 * (index / dx1);
					Color result = color + color1;
					m_rtexture.SetPixelColor(int(x), int(y), result);
				}
				else if (xMin == p_x2)
				{
					Color color = p_color2 * ((dx1 - index) / dx1);
					Color color1 = p_color1 * (index / dx1);
					Color result = color + color1;
					m_rtexture.SetPixelColor(int(x), int(y), result);
				}
			++index;
	    }
	}
	else
	{	
		float yMin, yMax;
		const float slope = dx / dy;

		if (p_y1 < p_y2)
		{
			yMin = p_y1;
			yMax = p_y2;
		}
		else
		{
			yMin = p_y2;
			yMax = p_y1;
		}
		
		for (float y = yMin; y <= yMax; ++y)
		{
			float x = p_x1 + ((y - p_y1) * slope);
				if (yMin == p_y1)
				{
					Color color = ((p_color2 / dy1) * (index));
					Color color1 = ((p_color1 / dy1) * (dy1 - index));
					Color result = color + color1;
					m_rtexture.SetPixelColor(int(x), int(y), result);
				}
				else if (yMin == p_y2)
				{
					Color color = ((p_color1 / dy1) * (index));
					Color color1 = ((p_color2 / dy1) * (dy1 - index));
					Color result = color + color1;
					m_rtexture.SetPixelColor(int(x), int(y), result);
				}
			++index;
		}
	}
}

void Rasterizer::DrawTriangle(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	
	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	const Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;
	
	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);

	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= 0.0 && bary.y >= 0.0 && bary.x + bary.y <= 1.0)
			{
				positions.z = v0.position.z * bary.z + v1.position.z * bary.x + bary.y * v2.position.z;
				if (m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] > positions.z)
				{
					m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] = positions.z;
					Color pixelColor;
					pixelColor.r =  p_v0.color.r * bary.z + p_v1.color.r * bary.x + p_v2.color.r * bary.y;
					pixelColor.g = p_v0.color.g * bary.z + p_v1.color.g * bary.x + p_v2.color.g * bary.y;
					pixelColor.b = p_v0.color.b * bary.z + p_v1.color.b * bary.x + p_v2.color.b * bary.y;
					m_rtexture.SetPixelColor(int(positions.x), int(positions.y), pixelColor);
				}
			}
		}
	}
}

void Rasterizer::DrawTriangleBlinnPhong(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_lightPosition, Vec3& p_lightcomp) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));

	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y <= 1)
			{
				positions.z = v0.position.z * bary.z + v1.position.z * bary.y + bary.x * v2.position.z;
				if (m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] > positions.z)
				{
					m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] = positions.z;
					Vec3 normal(bary.z * p_v0.normal.x + bary.y * p_v1.normal.x + bary.x * p_v2.normal.x,
								bary.z * p_v0.normal.y + bary.y * p_v1.normal.y + bary.x * p_v2.normal.y,
								bary.z * p_v0.normal.z + bary.y * p_v1.normal.z + bary.x * p_v2.normal.z);

					normal.Normalize();
					Color pixelColor;
					pixelColor.r = p_v0.color.r * bary.z + p_v1.color.r * bary.x + p_v2.color.r * bary.y;
					pixelColor.g = p_v0.color.g * bary.z + p_v1.color.g * bary.x + p_v2.color.g * bary.y;
					pixelColor.b = p_v0.color.b * bary.z + p_v1.color.b * bary.x + p_v2.color.b * bary.y;
					Color finalColor = this->BlinnPhongColor(positions, normal, p_lightPosition, p_lightcomp, pixelColor);
					m_rtexture.SetPixelColor(int(positions.x), int(positions.y), finalColor);
				}
			}
		}
	}
}

void Rasterizer::DrawTrianglePhong(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Vertex& p_light1, Vertex& p_light2, Vertex& p_light3, Vec3& p_lightcomp) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));

	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	Vec3 normal1(p_light1.normal.x, p_light1.normal.y, p_light1.normal.z);
	Vec3 normal2(p_light2.normal.x, p_light2.normal.y, p_light2.normal.z);
	Vec3 normal3(p_light3.normal.x, p_light3.normal.y, p_light3.normal.z);

	const Color c0 = this->PhongColor(p_light1, normal1, p_lightcomp, p_v0.color);
	const Color c1 = this->PhongColor(p_light2, normal2, p_lightcomp, p_v1.color);
	const Color c2 = this->PhongColor(p_light3, normal3, p_lightcomp, p_v2.color);
	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y < 1)
			{
				positions.z = v0.position.z * bary.z + v1.position.z * bary.y + bary.x * v2.position.z;
				if (m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] > positions.z)
				{
					m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] = positions.z;
					Color pixelColor;
					pixelColor.r = c0.r * bary.z + c1.r * bary.y + c2.r * bary.x;
					pixelColor.g = c0.g * bary.z + c1.g * bary.y + c2.g * bary.x;
					pixelColor.b = c0.b * bary.z + c1.b * bary.y + c2.b * bary.x;
					m_rtexture.SetPixelColor(int(positions.x), int(positions.y), pixelColor);
				}
			}
		}
	}
}

void Rasterizer::DrawTriangleWire(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	const Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	const Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	const Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	
	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	const Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	DrawLine(v0.position.x, v0.position.y, v1.position.x, v1.position.y, p_v0.color, p_v1.color);
	DrawLine(v1.position.x, v1.position.y, v2.position.x, v2.position.y, p_v1.color, p_v2.color);
	DrawLine(v2.position.x, v2.position.y, v0.position.x, v0.position.y, p_v2.color, p_v0.color);
}

void Rasterizer::DrawTriangleTexture(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Image* p_image) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	const Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y < 1)
			{
				const float u = p_v0.texCoordinate.x * bary.z + p_v1.texCoordinate.x * bary.y + p_v2.texCoordinate.x * bary.x;
				const float u2 = p_v0.texCoordinate.y * bary.z + p_v1.texCoordinate.y * bary.y + p_v2.texCoordinate.y * bary.x;

				const int ImgX = u * p_image->GetImageWidth();
				const int ImgY = u2 * p_image->GetImageHeight();
				Color final;
				final.r = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].r;
				final.g = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].g;
				final.b = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].b;
				final.a = 255.f;

				if (final.r == 255 && final.g == 0 && final.b == 255)
					continue;

				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
			}
		}
	}
}

void Rasterizer::DrawTriangleAlphaBlending(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2, Image* p_image, float p_alpha) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	const Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y < 1)
			{
				const float u = p_v0.texCoordinate.x * bary.z + p_v1.texCoordinate.x * bary.y + p_v2.texCoordinate.x * bary.x;
				const float u2 = p_v0.texCoordinate.y * bary.z + p_v1.texCoordinate.y * bary.y + p_v2.texCoordinate.y * bary.x;

				const int ImgX = u * p_image->GetImageWidth();
				const int ImgY = u2 * p_image->GetImageHeight();
				Color background; 
				background.r = m_rtexture.GetPixelColor(int(positions.x), int(positions.y)).r;
				background.g = m_rtexture.GetPixelColor(int(positions.x), int(positions.y)).g;
				background.b = m_rtexture.GetPixelColor(int(positions.x), int(positions.y)).b;
				Color source, final;
				source.r = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].r;
				source.g = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].g;
				source.b = p_image->GetColorTable()[ImgX + ImgY * p_image->GetImageWidth()].b;
				final.r = p_alpha * source.r + (1.f - p_alpha) * background.r;
				final.g = p_alpha * source.g + (1.f - p_alpha) * background.g;
				final.b = p_alpha * source.b + (1.f - p_alpha) * background.b;
				final.a = 255.0f * p_alpha;
				
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);

			}
		}
	}
}

void Rasterizer::DrawTriangleNoAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	
	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec2 positions(0, 0);
	Color final(p_v0.color.r, p_v0.color.g, p_v0.color.b);
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= -0.001f && bary.y >= -0.001f && bary.x + bary.y <= 1.001f)
			{
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
			}
		}
	}
}

void Rasterizer::DrawTriangle2XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));


	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec2 positions(0, 0);
	Color pre(255, 0, 0);
	float in = 0;
	float out = 0;
	float perX = 0.5f;
	float perY = 0.5f;
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= -0.01 && bary.y >= -0.01 && bary.x + bary.y < 1.01f)
			{
				for (uint8_t y = 0; y < 1; ++y)
				{
					for (uint8_t x = 0; x < 1; ++x)
					{
						float samplePosX = positions.x + perX * (x + 1);
						float samplePosY = positions.y + perY * (y + 1);
						const Vec3 barytest(triangle.Barycentric2(v0.position.x, v0.position.y, samplePosX, samplePosY));
						if (barytest.x >= -0.001f && barytest.y >= -0.001f && bary.x + barytest.y <= 1.0f)
						{
							in++;
						}
						else
						{
							out++;
						}
					}
				}
				float average = in / (in + out);
				Color final;
				final.r = p_v0.color.r * average;
				final.g = p_v0.color.g * average;
				final.b = p_v0.color.b * average;
				final.a = 255.0;
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
				in = 0;
				out = 0;
			}
		}
	}
}

void Rasterizer::DrawTriangle4XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));


	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec2 positions(0, 0);
	Color pre(255, 0, 0);
	float in = 0;
	float out = 0;
	float perX = 1.f / 2;
	float perY = 1.f / 2;
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= -0.01 && bary.y >= -0.01 && bary.x + bary.y < 1.01f)
			{
				for (uint8_t y = 0; y < 2; ++y)
				{
					for (uint8_t x = 0; x < 4; ++x)
					{
						float samplePosX = positions.x + perX * (x + 1);
						float samplePosY = positions.y + perY * (y + 1);
						const Vec3 barytest(triangle.Barycentric2(v0.position.x, v0.position.y, samplePosX, samplePosY));
						if (barytest.x >= -0.001f && barytest.y >= -0.001f && bary.x + barytest.y <= 1.0f)
						{
							in++;
						}
						else
						{
							out++;
						}
					}
				}
				float average = in / (in + out);
				Color final;
				final.r = p_v0.color.r * average;
				final.g = p_v0.color.g * average;
				final.b = p_v0.color.b * average;
				final.a = 255.0;
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
				in = 0;
				out = 0;
			}
		}
	}
}

void Rasterizer::DrawTriangle8XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));

	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec2 positions(0, 0);
	float in = 0;
	float out = 0;
	float perX = 1.f / 4;
	float perY = 1.f / 2;
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= -0.01 && bary.y >= -0.01 && bary.x + bary.y < 1.01f)
			{
				for (uint8_t y = 0; y < 2; ++y)
				{
					for (uint8_t x = 0; x < 4; ++x)
					{
						float samplePosX = positions.x + perX * (x + 1);
						float samplePosY = positions.y + perY * (y + 1);
						const Vec3 barytest(triangle.Barycentric2(v0.position.x, v0.position.y, samplePosX, samplePosY));
						if (barytest.x >= -0.001f && barytest.y >= -0.001f && bary.x + barytest.y <= 1.0f)
						{
							in++;
						}
						else
						{
							out++;
						}
					}
				}
				float average = in / (in + out);
				Color final;
				final.r = p_v0.color.r * average;
				final.g = p_v0.color.g * average;
				final.b = p_v0.color.b * average;
				final.a = 255.0;
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
				in = 0;
				out = 0;
			}
		}
	}
}

void Rasterizer::DrawTriangle16XAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));


	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	Vec2 positions(0, 0);
	float in = 0;
	float out = 0;
	float perX = 1.f / 4;
	float perY = 1.f / 4;
	for (positions.y = minY; positions.y <= maxY; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x >= -0.01 && bary.y >= -0.01 && bary.x + bary.y < 1.01f)
			{
				for (uint8_t y = 0; y < 4; ++y)
				{
					for (uint8_t x = 0; x < 4; ++x)
					{
						float samplePosX = positions.x + perX * (x + 1);
						float samplePosY = positions.y + perY * (y + 1);
						const Vec3 barytest(triangle.Barycentric2(v0.position.x, v0.position.y, samplePosX, samplePosY));
						if (barytest.x >= -0.001f && barytest.y >= -0.001f && bary.x + barytest.y <= 1.0f)
						{
							in++;
						}
						else
						{
							out++;
						}
					}
				}
				float average = in / (in + out);
				Color final;
				final.r = p_v0.color.r * average;
				final.g = p_v0.color.g * average;
				final.b = p_v0.color.b * average;
				final.a = 255.0;
				m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
				in = 0;
				out = 0;
			}
		}
	}
}

void Rasterizer::DrawTriangleForAntialiasing(Vertex& p_v0, Vertex& p_v1, Vertex& p_v2) const
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vec2 v(v1.position.x - v0.position.x, v1.position.y - v0.position.y);
	const Vec2 w(v2.position.x - v0.position.x, v2.position.y - v0.position.y);
	const float area = v.Cross(w);
	if (area < 0)
		return;

	Triangle triangle(v0, v1, v2);
	const AABB box = triangle.GetAABB();
	const int minX = std::max(static_cast<int>(box.minPoint.x), 0);
	const int minY = std::max(static_cast<int>(box.minPoint.y), 0);
	const int maxX = std::min(static_cast<int>(box.maxPoint.x), m_rtexture.GetWidth() - 1);
	const int maxY = std::min(static_cast<int>(box.maxPoint.y), m_rtexture.GetHeight() - 1);
	float in = 0;
	float out = 0;
	float perX = 1.f / 4;
	float perY = 1.f / 4;
	Vec3 positions(0, 0, 0);
	for (positions.y = minY; positions.y <= maxY ; ++positions.y)
	{
		for (positions.x = minX; positions.x <= maxX ; ++positions.x)
		{
			const Vec3 bary(triangle.Barycentric2(v0.position.x, v0.position.y, positions.x, positions.y));
			if (bary.x > -0.02 && bary.y > -0.02 && bary.x + bary.y < 1.02)
			{
				positions.z = v0.position.z * bary.z + v1.position.z * bary.x + bary.y * v2.position.z;
				if (m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] > positions.z)
				{
					m_zBuffer[int(positions.x + positions.y * Window::WIDTH)] = positions.z;
					Color current = m_rtexture.GetPixelColor(positions.x, positions.y);
					if(current.r == 0.f && current.g == 0.f && current.b == 0.f)
					{
						for (uint8_t y = 0; y < 4; ++y)
						{
							for (uint8_t x = 0; x < 4; ++x)
							{
								float samplePosX = positions.x + perX * (x + 1);
								float samplePosY = positions.y + perY * (y + 1);
								const Vec3 barytest(triangle.Barycentric2(v0.position.x, v0.position.y, samplePosX, samplePosY));
								if (barytest.x >= -0.01f && barytest.y >= -0.01f && barytest.x + barytest.y < 1.013f)
								{
									in++;
								}
								else
								{
									out++;
								}
							}
						}
						float average = in / (in + out);
						Color final;
						final.r = p_v0.color.r * average;
						final.g = p_v0.color.g * average;
						final.b = p_v0.color.b * average;
						final.a = 255.0;
						m_rtexture.SetPixelColor(int(positions.x), int(positions.y), final);
						in = 0;
						out = 0;
					}
				}
			}
		}
	}
}

void Rasterizer::ClearBuffer() const
{
	for (uint16_t i = m_rtexture.GetWidth() * m_rtexture.GetHeight(); i--;)
		m_zBuffer[i] = std::numeric_limits<float>::max();
}

Color Rasterizer::PhongColor(Vertex& p_position, Vec3& p_normal, Vec3& p_lightcomp, Color& p_color) const
{
	Vec3 lightDir(p_position.position);
	lightDir.Normalize();

	Vec3 viewDir = p_position.position *-1;
	viewDir.Normalize();

	const float lambert = std::max(lightDir.dot(p_normal), 0.0f);
	float specular = 0.0f;

	if (lambert > 0.0)
	{
		const float specAngle = p_normal.dot((p_normal + lightDir) / 2.0f);
		specular = powf(specAngle, 5.0);
	}
	const Color amb = p_color * m_sharedContext.appInfos.lightParams.ambiant / 100.f *(p_lightcomp.x);
	const Color diff = p_color * m_sharedContext.appInfos.lightParams.diffuse / 100.f * (p_lightcomp.y * lambert);
	const Color spec = p_color * m_sharedContext.appInfos.lightParams.specular / 100.f * (p_lightcomp.z * specular);
	Color total = amb + diff + spec;
	return total;
}

Color Rasterizer::BlinnPhongColor(Vec3& p_position, Vec3& p_normal, Vertex& p_lightPosition, Vec3& p_lightcomp,
	Color& p_color) const
{
	const Vertex position1(Mat4::ScreenToView(p_position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vec3 lightDir(p_lightPosition.position.x - position1.position.x, p_lightPosition.position.y - position1.position.y, p_lightPosition.position.z - position1.position.z);
	lightDir.Normalize();

	const float lambert = std::max(lightDir.dot(p_normal), 0.0f);
	float specular = 0.0f;

	if (lambert > 0.0f)
	{
		Vec3 viewDir(-position1.position.x, -position1.position.y, -position1.position.z);
		viewDir.Normalize();

		Vec3 halfDir(lightDir.x + viewDir.x, lightDir.y + viewDir.y, lightDir.z + viewDir.z);
		halfDir.Normalize();

		const float specAngle = std::max(halfDir.dot(p_normal), 0.0f);
		specular = powf(specAngle, 40.0);
	}

	// TODO: Put ambiant, diff and spec values in the appInfos and add the possibility to change it "in-game"
	Color amb, diff, spec;
	amb.r = p_color.r * m_sharedContext.appInfos.lightParams.ambiant / 100.f * p_lightcomp.x;
	amb.g = p_color.g * m_sharedContext.appInfos.lightParams.ambiant / 100.f * p_lightcomp.x;
	amb.b = p_color.b * m_sharedContext.appInfos.lightParams.ambiant / 100.f * p_lightcomp.x;

	diff.r = p_color.r * m_sharedContext.appInfos.lightParams.diffuse / 100.f * (p_lightcomp.y * lambert);
	diff.g = p_color.g * m_sharedContext.appInfos.lightParams.diffuse / 100.f * (p_lightcomp.y * lambert);
	diff.b = p_color.b * m_sharedContext.appInfos.lightParams.diffuse / 100.f * (p_lightcomp.y * lambert);

	spec.r = p_color.r * m_sharedContext.appInfos.lightParams.specular / 100.f * (p_lightcomp.z * specular);
	spec.g = p_color.g * m_sharedContext.appInfos.lightParams.specular / 100.f * (p_lightcomp.z * specular);
	spec.b = p_color.b * m_sharedContext.appInfos.lightParams.specular / 100.f * (p_lightcomp.z * specular);

	return Color(amb.r + diff.r + spec.r, amb.g + diff.g + spec.g, amb.b + diff.b + spec.b);
}

void Rasterizer::DrawSpan(const Span& p_span, const float p_y) const
{
	const float dx = p_span.x2 - p_span.x1;
	if (dx == 0)
		return;

	const Color dColor = p_span.color2 - p_span.color1;
	float factor = 0.0f;
	const float factorSpan = 1.0f / dx;
	for (int x = p_span.x1; x < p_span.x2; x++)
	{
		Color result(p_span.color1 + (dColor * factor));
		m_rtexture.SetPixelColor(x, p_y, result);
		factor += factorSpan;
	}
}

void Rasterizer::FillTriangle(const Edge& p_edge1, const Edge& p_edge2) const
{
	const float dyEdge1 = p_edge1.y2 - p_edge1.y1;
	if (dyEdge1 == 0)
		return;

	const float dyEdge2 = p_edge2.y2 - p_edge2.y1;
	if (dyEdge2 == 0)
		return;

	const float dxEdge1 = p_edge1.x2 - p_edge1.x1;
	const float dxEdge2 = p_edge2.x2 - p_edge2.x1;
	const Color dEdge1Col = p_edge1.color2 - p_edge1.color1;
	const Color dEdge2Col = p_edge2.color2 - p_edge2.color1;
	
	float factor1 = (p_edge2.y1 - p_edge1.y1) / dyEdge1;
	const float factorSpan1 = 1.0f / dyEdge1;
	float factor2 = 0.0f;
	const float factorSpan2 = 1.0f / dyEdge2;
	for (int y = p_edge2.y1; y < p_edge2.y2; ++y) 
	{	
		const Span span(p_edge1.x1 + (dxEdge1 * factor1),
				  p_edge2.x1 + (dxEdge2 * factor2),
				  p_edge1.color1 + (dEdge1Col * factor1),
				  p_edge2.color1 + (dEdge2Col * factor2));
		DrawSpan(span, y);
		factor1 += factorSpan1;
		factor2 += factorSpan2;
	}
}
