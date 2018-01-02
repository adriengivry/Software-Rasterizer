#include "../include/Rasterizer.h"
namespace Mat3Dto2D
{
	Mat4 model;
	Mat4 view;
	Mat4 projection;
};
using namespace Mat3Dto2D;

Rasterizer::Rasterizer(Texture& p_texture, SDL_Renderer& p_renderer, SDL_Texture& p_texture1) :
	m_rtexture(p_texture),
	m_renderer(p_renderer),
	m_texture(p_texture1),
	m_wireFrame(false),
	m_zBuffer(new float[m_rtexture.GetWidth() * m_rtexture.GetHeight()])
{
	//clearZBuffer();
}

Rasterizer::~Rasterizer()
{
	delete[] m_zBuffer;
}

void Rasterizer::RenderScene(Scene * p_pScene)
{
	
}
void Rasterizer::update()
{
	//drawZBuffer();
	SDL_UpdateTexture(&m_texture, nullptr, m_rtexture.GetPixelBuffer(), m_rtexture.GetWidth() * sizeof(uint32_t));
	SDL_RenderCopy(&m_renderer, &m_texture, nullptr, nullptr);
	SDL_RenderPresent(&m_renderer);
	m_rtexture.ClearBuffer();
	SDL_RenderClear(&m_renderer);
	
	//clearZBuffer();
}

void Rasterizer::drawLine(const float p_x1,const float p_y1,const float p_x2,const float p_y2, Color& p_color1, Color& p_color2)
{
	float dx = p_x2 - p_x1;
	float dy = p_y2 - p_y1;
	float dx1 = fabs(p_x2 - p_x1);
	float dy1 = fabs(p_y2 - p_y1);
	if (dx == 0.0f && dy == 0.0f)
	{
		m_rtexture.SetPixelColor(p_x1, p_y1, p_color1);
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
		for (uint16_t x = xMin; x <= xMax; x++)
		{
			float y = p_y1 + ((x - p_x1) * slope);
			if (xMin == p_x1)
			{
				Color color = p_color1 * ((dx1 - index)/dx1);
				Color color1 = p_color2 * (index/dx1);
				m_rtexture.SetPixelColor(x, y, color + color1);
			}
			else if (xMin == p_x2)
			{
				Color color = p_color2 * ((dx1 - index)/dx1);
				Color color1 = p_color1 * (index/dx1);
				m_rtexture.SetPixelColor(x, y, color + color1);
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
		for (uint16_t y = yMin; y <= yMax; y++)
		{
			float x = p_x1 + ((y - p_y1) * slope);
			if (yMin == p_y1)
			{
				Color color = ((p_color2 / dy1) * (index));
				Color color1 = ((p_color1 / dy1) * (dy1 - index));
				m_rtexture.SetPixelColor(x, y, (color + color1));
			}
			else if (yMin == p_y2)
			{
				Color color = ((p_color1 / dy1) * (index));
				Color color1 = ((p_color2 / dy1) * (dy1 - index));
				m_rtexture.SetPixelColor(x, y, (color + color1));
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

	if (m_wireFrame)
	{
		drawLine(v0.position.x, v0.position.y, v1.position.x, v1.position.y, v0.color, v1.color);
		drawLine(v1.position.x, v1.position.y, v2.position.x, v2.position.y, v1.color, v2.color);
		drawLine(v2.position.x, v2.position.y, v0.position.x, v0.position.y, v2.color, v0.color);
	}
	else
	{
		bool uniColor = false;
		Color colorV0 = p_v0.color;
		Color colorV1 = p_v1.color;
		Color colorV2 = p_v2.color;
		if (colorV0 == colorV1 && colorV0 == colorV2)
		{
			uniColor = true;
		}
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
				Vec3 barycent(triangle.Barycentric(v0, v1, v2, positions));
				if (barycent.x >= 0 && barycent.y >= 0 && barycent.x + barycent.y < 1 && uniColor)
				{
					m_rtexture.SetPixelColor(positions.position.x, positions.position.y, colorV0);
				}
				else if (barycent.x >= 0 && barycent.y >= 0 && barycent.x + barycent.y < 1 && !uniColor)
				{
					m_rtexture.SetPixelColor(positions.position.x, positions.position.y, ((colorV1 * barycent.x) + (colorV2 * barycent.y) + (colorV0 * barycent.z)));
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
	v00 = pvm * v00;
	v01 = pvm * v01;
	v02 = pvm * v02;

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

void Rasterizer::drawZBuffer()
{
	for (uint16_t x = 0; x < m_rtexture.GetWidth(); x++) {
		for (uint16_t y = 0; y < m_rtexture.GetHeight(); y++) {
			float shading = (1 + m_zBuffer[y * m_rtexture.GetWidth() + x]) / 2;
			if (shading < 0) {
				shading = 0;
			}
			Color temp((255, 0 ,0 , 255));
			m_rtexture.SetPixelColor(x, y, temp);
		}
	}
}

void Rasterizer::clearZBuffer()
{
	for (uint16_t i = 0; i < m_rtexture.GetWidth() * m_rtexture.GetHeight(); i++)
	{
		m_zBuffer[i] = std::numeric_limits<float>::infinity();
	}
}

void Rasterizer::BeginDraw()
{
	model = Mat4().Identity();
	view = Mat4().Identity();
	projection = Mat4().Identity();
	projection = Mat4::CreatePerspective(60, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.1f, 100.0f);
	view = Mat4::CreateView(3, 1, 5, 0, 0, 0, 0, 1, 0);
}

void Rasterizer::EndDraw()
{
	model = Mat4().Identity();
	view = Mat4().Identity();
	projection = Mat4().Identity();
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
