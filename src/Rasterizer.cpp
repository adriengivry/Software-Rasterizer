#include "../include/Rasterizer.h"

Rasterizer::Rasterizer(Texture& p_texture, SDL_Renderer& p_renderer, SDL_Texture& p_texture1) :
	m_rtexture(p_texture),
	m_renderer(p_renderer),
	m_texture(p_texture1),
	m_wireFrame(false)
{}

Rasterizer::~Rasterizer()
{}

void Rasterizer::RenderScene(Scene * p_pScene)
{
	
}
void Rasterizer::update()
{
	SDL_UpdateTexture(&m_texture, nullptr, m_rtexture.GetPixelBuffer(), m_rtexture.GetWidth() * sizeof(uint32_t));
	SDL_RenderCopy(&m_renderer, &m_texture, nullptr, nullptr);
	SDL_RenderPresent(&m_renderer);
	m_rtexture.ClearBuffer();
	SDL_RenderClear(&m_renderer);
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
					m_rtexture.SetPixelColor(positions.position.x, positions.position.y, ((colorV1 * barycent.y) + (colorV2 * barycent.x) + (colorV0 * barycent.z)));
				}
			}
		}

	}
}
