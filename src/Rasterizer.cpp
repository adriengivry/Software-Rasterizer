#include "../include/Rasterizer.h"
#include <math.h>

namespace Mat3Dto2D
{
	Mat4 model;
	Mat4 view;
	Mat4 projection;
	Mat4 SphereModel;
};
using namespace Mat3Dto2D;

Rasterizer::Rasterizer(Texture& p_texture, SDL_Renderer& p_renderer, SDL_Texture& p_texture1) :
	m_rtexture(p_texture),
	m_renderer(p_renderer),
	m_texture(p_texture1),
	m_wireFrame(false),
	m_zBuffer(new float[m_rtexture.GetWidth() * m_rtexture.GetHeight()])
{
	for (int i = m_rtexture.GetWidth() * m_rtexture.GetHeight(); i--;)
		m_zBuffer[i] = std::numeric_limits<float>::max();
}

Rasterizer::~Rasterizer()
{
	delete[] m_zBuffer;
}

void Rasterizer::RenderScene(Scene * p_pScene)
{
	for (uint16_t j = 0; j < p_pScene->m_entities.size(); j++)
	{
		Mat4 normalMatrix = p_pScene->m_entities[j]->GetMatrix();
		Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		for (int i = 0; i < p_pScene->m_entities[j]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 2]]);
			//v0.VertexTransform(positionMatrix, normalMatrix);
			//v1.VertexTransform(positionMatrix, normalMatrix);
			//v2.VertexTransform(positionMatrix, normalMatrix);
			drawTriangle(v0, v1, v2);
		}
	}
}
void Rasterizer::RenderScene2(Scene * p_pScene)
{
	
	Vertex lightposition = p_pScene->m_lights[0]->GetPosition();
	Vec3 Lightcomp(p_pScene->m_lights[0]->GetAmbient(), p_pScene->m_lights[0]->GetDiffuse(), p_pScene->m_lights[0]->GetSpecular());
	lightposition.VertexTransform(Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f));
	//Vertex lightlast(Mat4::ConvertToScreen(lightposition.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	for (uint16_t j = 0; j < p_pScene->m_entities.size(); j++)
	{
		Mat4 normalMatrix = p_pScene->m_entities[j]->GetMatrix();
		Mat4 projection = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Mat4 normalMatrixTrans = normalMatrix.CreateInverse();
		normalMatrixTrans = normalMatrixTrans.CreateTranspose();
		for (int i = 0; i < p_pScene->m_entities[j]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 2]]);
			v0.VertexTransform(projection);
			v1.VertexTransform(projection);
			v2.VertexTransform(projection);
			v0.NormalTransform(normalMatrixTrans);
			v1.NormalTransform(normalMatrixTrans);
			v2.NormalTransform(normalMatrixTrans);
			
			drawTriangle2(v0, v1, v2, lightposition, Lightcomp);
		}
	}
}
void Rasterizer::RenderScene3(Scene * p_pScene)
{
	for (uint16_t j = 0; j < p_pScene->m_entities.size(); j++)
	{
		Mat4 normalMatrix = p_pScene->m_entities[j]->GetMatrix();
		Mat4 projection1 = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		Mat4 normalMatrixTrans = normalMatrix.CreateTranspose();
		normalMatrixTrans = normalMatrixTrans.CreateInverse();
		Vertex lightposition = p_pScene->m_lights[0]->GetPosition();
		Vec3 Lightcomp(p_pScene->m_lights[0]->GetAmbient(), p_pScene->m_lights[0]->GetDiffuse(), p_pScene->m_lights[0]->GetSpecular());
		for (int i = 0; i < p_pScene->m_entities[j]->GetMesh()->GetIndices().size() - 2; i += 3)
		{
			Vertex v0 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 2]]);
			Vertex light1 = v0.firstTransform(normalMatrix, normalMatrixTrans);
			Vertex light2 = v1.firstTransform(normalMatrix, normalMatrixTrans);
			Vertex light3 = v2.firstTransform(normalMatrix, normalMatrixTrans);
			v0.VertexTransform(projection1);
			v1.VertexTransform(projection1);
			v2.VertexTransform(projection1);
			drawTriangle3(v0, v1, v2, light1, light2, light3, lightposition, Lightcomp);
		}
	}
}
void Rasterizer::RenderScenewire(Scene * p_pScene)
{
	for (uint16_t j = 0; j < p_pScene->m_entities.size(); j++)
	{
		Mat4 normalMatrix = p_pScene->m_entities[j]->GetMatrix();
		Mat4 positionMatrix = Mat4::CreatePerspective(60, float(m_rtexture.GetWidth()) / float(m_rtexture.GetHeight()), 0.1f, 100.0f) * normalMatrix;
		for (int i = 0; i < p_pScene->m_entities[j]->GetMesh()->GetIndices().size() - 2; i +=3)
		{
			Vertex v0 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i]]);
			Vertex v1 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 1]]);
			Vertex v2 = (p_pScene->m_entities[j]->GetMesh()->GetVertices()[p_pScene->m_entities[j]->GetMesh()->GetIndices()[i + 2]]);
			v0.VertexTransform(positionMatrix);
			v1.VertexTransform(positionMatrix);
			v2.VertexTransform(positionMatrix);
			drawTiangleWire(v0, v1, v2);
		}
	}
}
void Rasterizer::update()
{
	SDL_UpdateTexture(&m_texture, nullptr, m_rtexture.GetPixelBuffer(), m_rtexture.GetWidth() * sizeof(uint32_t));
	SDL_RenderCopy(&m_renderer, &m_texture, nullptr, nullptr);
	SDL_RenderPresent(&m_renderer);
	m_rtexture.ClearBuffer();
	SDL_RenderClear(&m_renderer);
	for (int i = m_rtexture.GetWidth() * m_rtexture.GetHeight(); i--;)
		m_zBuffer[i] = std::numeric_limits<float>::max();
}

void Rasterizer::drawLine(const float p_x1,const float p_y1,const float p_x2,const float p_y2, Color p_color1, Color p_color2)
{
	float dx = p_x2 - p_x1;
	float dy = p_y2 - p_y1;
	float dx1 = fabs(p_x2 - p_x1);
	float dy1 = fabs(p_y2 - p_y1);
	if (dx == 0.0f && dy == 0.0f)
	{
		m_rtexture.SetPixelColor(int(p_x1), int(p_y1), p_color1);
		return;
	}
	float index = 0;
	if (fabs(dx) > fabs(dy))
	{
		float xMin, xMax;
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
		float slope = dy / dx;
		for (float x = xMin; x <= xMax; x++)
		{
			float y = p_y1 + ((x - p_x1) * slope);
				if (xMin == p_x1)
				{
					Color color = p_color1 * ((dx1 - index) / dx1);
					Color color1 = p_color2 * (index / dx1);
					m_rtexture.SetPixelColor(int(x), int(y), color + color1);
				}
				else if (xMin == p_x2)
				{
					Color color = p_color2 * ((dx1 - index) / dx1);
					Color color1 = p_color1 * (index / dx1);
					m_rtexture.SetPixelColor(int(x), int(y), color + color1);
				}
			++index;
	    }
	}
	else
	{	
		float yMin, yMax;
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
		float slope = dx / dy;
		for (float y = yMin; y <= yMax; y++)
		{
			float x = p_x1 + ((y - p_y1) * slope);
				if (yMin == p_y1)
				{
					Color color = ((p_color2 / dy1) * (index));
					Color color1 = ((p_color1 / dy1) * (dy1 - index));
					m_rtexture.SetPixelColor(int(x), int(y), color + color1);
				}
				else if (yMin == p_y2)
				{
					Color color = ((p_color1 / dy1) * (index));
					Color color1 = ((p_color2 / dy1) * (dy1 - index));
					m_rtexture.SetPixelColor(int(x), int(y), color + color1);
				}
			++index;
		}
	}
}

void Rasterizer::drawTriangle(Vertex p_v0, Vertex p_v1, Vertex p_v2)
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Triangle triangle(v0, v1, v2);
	AABB box = triangle.getAABB();
	int minX = std::max((int)box.minPoint.x, 0);
	int minY = std::max((int)box.minPoint.y, 0);
	int maxX = std::min((int)box.maxPoint.x, m_rtexture.GetWidth() - 1);
	int maxY = std::min((int)box.maxPoint.y, m_rtexture.GetHeight() - 1);
	Vertex positions(0, 0, 0);
	for (positions.position.y = minY; positions.position.y <= maxY; positions.position.y++)
	{
		for (positions.position.x = minX; positions.position.x <= maxX; positions.position.x++)
		{
			Vec3 bary(triangle.Barycentric(v0, v1, v2, positions));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y < 1)
			{
				positions.position.z = 0;
				positions.position.z = v0.position.z * bary.z + (v1.position.z) * bary.x + bary.y * (v2.position.z);
				if (m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] > positions.position.z)
				{
					m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] = positions.position.z;
					m_rtexture.SetPixelColor(int(positions.position.x), int(positions.position.y), (p_v0.color * bary.z + p_v1.color * bary.x + p_v2.color * bary.y));
				}
			}
		}
	}
}

void Rasterizer::drawTriangle2(Vertex p_v0, Vertex p_v1, Vertex p_v2, Vertex p_lightPosition, Vec3 p_lightcomp)
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));

	Triangle triangle(v0, v1, v2);
	AABB box = triangle.getAABB();
	int minX = std::max((int)box.minPoint.x, 0);
	int minY = std::max((int)box.minPoint.y, 0);
	int maxX = std::min((int)box.maxPoint.x, m_rtexture.GetWidth() - 1);
	int maxY = std::min((int)box.maxPoint.y, m_rtexture.GetHeight() - 1);
	Vertex positions(0, 0, 0);
	for (positions.position.y = minY; positions.position.y <= maxY; positions.position.y++)
	{
		for (positions.position.x = minX; positions.position.x <= maxX; positions.position.x++)
		{
			Vec3 bary(triangle.Barycentric(v0, v1, v2, positions));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y < 1)
			{
				positions.position.z = v0.position.z * bary.z + v1.position.z * bary.y + bary.x * v2.position.z;
				if (m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] > positions.position.z)
				{
					m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] = positions.position.z;
					Vec3 normal(bary.z * p_v0.normal.x + bary.y * p_v1.normal.x + bary.x * p_v2.normal.x,
								bary.z * p_v0.normal.y + bary.y * p_v1.normal.y + bary.x * p_v2.normal.y,
								bary.z * p_v0.normal.z + bary.y * p_v1.normal.z + bary.x * p_v2.normal.z);

					normal.Normalize();
					Color finalColor = this->BlinnPhongColor(positions, normal, p_lightPosition, p_lightcomp, (p_v0.color * bary.z + p_v1.color * bary.y + p_v2.color * bary.x));
					m_rtexture.SetPixelColor(int(positions.position.x), int(positions.position.y), finalColor);
				}
			}
		}
	}
}

void Rasterizer::drawTriangle3(Vertex p_v0, Vertex p_v1, Vertex p_v2, Vertex p_light1, Vertex p_light2, Vertex p_light3, Vertex p_lightPosition, Vec3 p_lightcomp)
{
	Color c0 = this->PhongColor(p_light1, Vec3(p_light1.normal.x, p_light1.normal.y, p_light1.normal.z), p_lightPosition, p_lightcomp, p_v0.color);
	Color c1 = this->PhongColor(p_light2, Vec3(p_light2.normal.x, p_light2.normal.y, p_light2.normal.z), p_lightPosition, p_lightcomp, p_v1.color);
	Color c2 = this->PhongColor(p_light3, Vec3(p_light3.normal.x, p_light3.normal.y, p_light3.normal.z), p_lightPosition, p_lightcomp, p_v2.color);

	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	
	Triangle triangle(v0, v1, v2);
	AABB box = triangle.getAABB();
	int minX = std::max((int)box.minPoint.x, 0);
	int minY = std::max((int)box.minPoint.y, 0);
	int maxX = std::min((int)box.maxPoint.x, m_rtexture.GetWidth() - 1);
	int maxY = std::min((int)box.maxPoint.y, m_rtexture.GetHeight() - 1);
	Vertex positions(0, 0, 0);
	for (positions.position.y = minY; positions.position.y <= maxY; positions.position.y++)
	{
		for (positions.position.x = minX; positions.position.x <= maxX; positions.position.x++)
		{
			Vec3 bary(triangle.Barycentric(v0, v1, v2, positions));
			if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y <= 1)
			{
				positions.position.z = v0.position.z * bary.z + (v1.position.z) * bary.y + bary.x * (v2.position.z);
				if (m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] > positions.position.z)
				{
					m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] = positions.position.z;
					m_rtexture.SetPixelColor(int(positions.position.x), int(positions.position.y), (c0 * bary.z + c1 * bary.y + c2 * bary.x));
				}
			}
		}
	}
}

void Rasterizer::drawTiangleWire(Vertex p_v0, Vertex p_v1, Vertex p_v2)
{
	Vertex v0(Mat4::ConvertToScreen(p_v0.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(p_v1.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(p_v2.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	

	drawLine(v0.position.x, v0.position.y, v1.position.x, v1.position.y, p_v0.color, p_v1.color);
	drawLine(v1.position.x, v1.position.y, v2.position.x, v2.position.y, p_v1.color, p_v2.color);
	drawLine(v2.position.x, v2.position.y, v0.position.x, v0.position.y, p_v2.color, p_v0.color);
}

void Rasterizer::drawTriangleSphere(Vertex p_v0, Vertex p_v1, Vertex p_v2)
{
	model = Mat4::CreateTranslation(0, 0, 3);
	Mat4 pvm = projection * view * SphereModel;
	Vec4 v00(p_v0.position);
	Vec4 v01(p_v1.position);
	Vec4 v02(p_v2.position);
	//v00 = pvm * v00;
	//v01 = pvm * v01;
	//v02 = pvm * v02;

	if (v00.w != 0)
		v00 /= v00.w;

	if (v01.w != 0)
		v01 /= v01.w;

	if (v02.w != 0)
		v02 /= v02.w;

	Vertex v0(Mat4::ConvertToScreen(Vec3(v00.x, v00.y, v00.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(Vec3(v01.x, v01.y, v01.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(Vec3(v02.x, v02.y, v02.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	if (m_wireFrame)
	{
		drawLine(v0.position.x, v0.position.y, v1.position.x, v1.position.y, v0.color, v1.color);
		drawLine(v1.position.x, v1.position.y, v2.position.x, v2.position.y, v1.color, v2.color);
		drawLine(v2.position.x, v2.position.y, v0.position.x, v0.position.y, v2.color, v0.color);
	}
	else
	{
		Triangle triangle(v0, v1, v2);
		AABB box = triangle.getAABB();
		int minX = std::max((int)box.minPoint.x, 0);
		int minY = std::max((int)box.minPoint.y, 0);
		int maxX = std::min((int)box.maxPoint.x, m_rtexture.GetWidth() - 1);
		int maxY = std::min((int)box.maxPoint.y, m_rtexture.GetHeight() - 1);
		Vertex positions(0, 0, 0);
		for (positions.position.y = minY; positions.position.y <= maxY; positions.position.y++)
		{
			for (positions.position.x = minX; positions.position.x <= maxX; positions.position.x++)
			{
				Vec3 bary(triangle.Barycentric(v0, v1, v2, positions));
				if (bary.x >= 0 && bary.y >= 0 && bary.x + bary.y <= 1)
				{
					positions.position.z = 0;
					positions.position.z = v0.position.z * bary.z + (v1.position.z) * bary.x + bary.y * (v2.position.z);
					if (m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] < positions.position.z)
					{
						m_zBuffer[int(positions.position.x + positions.position.y * WINDOW_WIDTH)] = positions.position.z;
						m_rtexture.SetPixelColor((int)positions.position.x, (int)positions.position.y, (p_v0.color * bary.z + p_v1.color * bary.x + p_v2.color * bary.y));
					}
				}
			}
		}
	}
}

void Rasterizer::drawTriangleSpan(Vertex p_v0, Vertex p_v1, Vertex p_v2)
{
	Mat4 pvm = projection * view * model;
	Vec4 v00(p_v0.position);
	Vec4 v01(p_v1.position);
	Vec4 v02(p_v2.position);
	//v00 = pvm * v00;
	//v01 = pvm * v01;
	//v02 = pvm * v02;

	//v00 = pvm * v00;
	//v01 = pvm * v01;
	//v02 = pvm * v02;
	if (v00.w != 0)
		v00 /= v00.w;
	
	if (v01.w != 0)
		v01 /= v01.w;

	if (v02.w != 0)
		v02 /= v02.w;

	Vertex v0(Mat4::ConvertToScreen(Vec3(v00.x, v00.y, v00.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v1(Mat4::ConvertToScreen(Vec3(v01.x, v01.y, v01.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vertex v2(Mat4::ConvertToScreen(Vec3(v02.x, v02.y, v02.z), m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Edge edges[3] =
	{
		Edge(v0.position.x, v0.position.y, v1.position.x, v1.position.y, p_v0.color, p_v1.color),
		Edge(v1.position.x, v1.position.y, v2.position.x, v2.position.y, p_v1.color, p_v2.color),
		Edge(v2.position.x, v2.position.y, v0.position.x, v0.position.y, p_v2.color, p_v0.color)
	};
	int maxLength = 0;
	int longEdge = 0;

	for (int i = 0; i < 3; i++)
	{
		int length = edges[i].y2 - edges[i].y1;
		if (length > maxLength)
		{
			maxLength = length;
			longEdge = i;
		}
	}
	int sEdge1 = (longEdge + 1) % 3;
	int sEdge2 = (longEdge + 2) % 3;
	FillTriangle(edges[longEdge], edges[sEdge1]);
	FillTriangle(edges[longEdge], edges[sEdge2]);
}

void Rasterizer::BeginDraw()
{
	//SphereModel = Mat4::Identity();
	//projection = Mat4::CreatePerspective(60, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.01f, 100.0f);
	//view = Mat4::CreateView(0, 0, 0, 0, 0, 0, 0, 1, 0);
	//model = Mat4::CreateTranslation(0, 2, 0);
}

void Rasterizer::ClearBuffer()
{
	for (int i = m_rtexture.GetWidth() * m_rtexture.GetHeight(); i--;)
		m_zBuffer[i] = -std::numeric_limits<float>::max();
}

Color Rasterizer::PhongColor(Vertex p_position, Vec3 p_normal, Vertex p_light, Vec3 p_lightcomp, Color p_color)
{
	Vec3 lightDir(p_light.position.x - p_position.position.x , p_light.position.y - p_position.position.y, p_light.position.z - p_position.position.z);
	lightDir.Normalize();
	Vec3 lightDirneg(-lightDir.x, -lightDir.y, -lightDir.z);

	Vec3 reflect = (p_normal * (2.0f * (p_normal.dot(lightDirneg)))) - lightDirneg;
	//reflect.Normalize();

	Vec3 viewDir(-p_position.position.x, -p_position.position.y, -p_position.position.z);
	viewDir.Normalize();

	float lambert = std::max(lightDir.dot(p_normal), 0.0f);
	float specular = 0.0f;

	if (lambert > 0.0)
	{
		float specAngle = std::max(reflect.dot(viewDir), 0.0f);
		specular = pow(specAngle, 10.0);
	}
	float amb = (p_lightcomp.x * 0.3);
	float diff = (p_lightcomp.y * lambert * 0.4);
	float spec = (p_lightcomp.z * specular);
	Color total =  p_color * (amb + diff + spec);
	return total;
}

Color Rasterizer::BlinnPhongColor(Vertex p_position, Vec3 p_normal, Vertex p_lightPosition, Vec3 p_lightcomp,
	Color p_color)
{
	Vertex position1(Mat4::ScreenToView(p_position.position, m_rtexture.GetWidth(), m_rtexture.GetHeight()));
	Vec3 lightDir(position1.position *-1);
	lightDir.Normalize();

	float lambert = std::max(lightDir.dot(p_normal), 0.0f);
	float specular = 0.0f;

	if (lambert > 0.0f)
	{
		Vec3 viewDir = (position1.position *-1);
		viewDir.Normalize();

		Vec3 halfDir = (lightDir + viewDir);
		halfDir.Normalize();

		float specAngle = std::max(halfDir.dot(p_normal), 0.0f);
		specular = pow(specAngle, 14.0);
	}
	Color amb = p_color * (p_lightcomp.x);
	Color diff = p_color * (p_lightcomp.y * lambert);
	Color spec = Color(255, 255, 255) * (p_lightcomp.z * specular);
	Color total = spec;
	return total;
}

void Rasterizer::DrawSpan(const Span& p_span, float p_y)
{
	float dx = p_span.x2 - p_span.x1;
	if (dx == 0)
		return;

	Color dColor = p_span.color2 - p_span.color1;
	float factor = 0.0f;
	float factorSpan = 1.0f / dx;
	for (int x = p_span.x1; x < p_span.x2; x++)
	{
		m_rtexture.SetPixelColor(x, p_y, p_span.color1 + (dColor * factor));
		factor += factorSpan;
	}
}


void Rasterizer::FillTriangle(const Edge& p_edge1, const Edge& p_edge2)
{
	float dyEdge1 = p_edge1.y2 - p_edge1.y1;
	if (dyEdge1 == 0)
		return;

	float dyEdge2 = p_edge2.y2 - p_edge2.y1;
	if (dyEdge2 == 0)
		return;

	float dxEdge1 = p_edge1.x2 - p_edge1.x1;
	float dxEdge2 = p_edge2.x2 - p_edge2.x1;
	Color dEdge1Col = p_edge1.color2 - p_edge1.color1;
	Color dEdge2Col = p_edge2.color2 - p_edge2.color1;
	
	float factor1 = (p_edge2.y1 - p_edge1.y1) / dyEdge1;
	float factorSpan1 = 1.0f / dyEdge1;
	float factor2 = 0.0f;
	float factorSpan2 = 1.0f / dyEdge2;
	for (int y = p_edge2.y1; y < p_edge2.y2; y++) 
	{	
		Span span(p_edge1.x1 + (dxEdge1 * factor1),
				  p_edge2.x1 + (dxEdge2 * factor2),
				  p_edge1.color1 + (dEdge1Col * factor1),
				  p_edge2.color1 + (dEdge2Col * factor2));
		DrawSpan(span, y);
		factor1 += factorSpan1;
		factor2 += factorSpan2;
	}
}
