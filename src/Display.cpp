#include "../include/Display.h"

Display::Display() : m_pRasterizer{nullptr}, m_pWindow(nullptr), m_pRenderer(nullptr), m_pTexture(nullptr), m_prTexture(nullptr), m_pScene(nullptr), m_pEntity(nullptr), ytransfrom(0)
{}

Display::~Display()
{
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	delete m_pRasterizer;
	delete m_prTexture;
	delete m_pScene;
	for (int i = 0; i < 2; ++i)
	{
		delete m_pEntity[i];
	}
	delete m_pEntity;
}

void Display::update()
{
	m_pRasterizer->update();
}

void Display::init()
{
	m_prTexture = new Texture(WINDOW_WIDTH, WINDOW_HEIGHT);
	m_pWindow = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);
	m_pRasterizer = new Rasterizer(*m_prTexture, *m_pRenderer, *m_pTexture);
}

void Display::initScene()
{
	m_pScene = new Scene();
	m_pEntity = new Entity*[2];
	for (int i = 0; i < 2; ++i)
	{
		m_pEntity[i] = new Entity();
	}
	m_pEntity[0]->SetMesh(*Mesh::CreateCube2());
	m_pEntity[1]->SetMesh(*Mesh::CreateSphere(20, 20));
	for (int i = 0; i < m_pEntity[0]->GetMesh()->GetVertices().size(); i++)
	{
		m_pEntity[0]->GetMesh()->GetVertices()[i].SetColor(255, 0, 0, 255);
	}
	for (int i = 0; i < m_pEntity[1]->GetMesh()->GetVertices().size(); i++)
	{
		m_pEntity[1]->GetMesh()->GetVertices()[i].SetColor(255, 0, 0, 255);
	}
	m_pScene->m_entities.push_back(m_pEntity[0]);
	m_pScene->m_entities.push_back(m_pEntity[1]);
}

void Display::RenderScene(Scene * p_pScene)
{
	m_pRasterizer->RenderScene(p_pScene);
}

void Display::drawLine()
{
	m_pRasterizer->BeginDraw();
	Mat3Dto2D::model = Mat4::CreateRotation(45, ytransfrom, 0);
	for (int i = 0; i < m_pScene->m_entities[0]->GetMesh()->GetIndices().size() - 3; i++)
	{
		m_pRasterizer->drawTriangleSpan(m_pScene->m_entities[0]->GetMesh()->GetVertices()[m_pScene->m_entities[0]->GetMesh()->GetIndices()[i]], m_pScene->m_entities[0]->GetMesh()->GetVertices()[m_pScene->m_entities[0]->GetMesh()->GetIndices()[i + 1]],
			m_pScene->m_entities[0]->GetMesh()->GetVertices()[m_pScene->m_entities[0]->GetMesh()->GetIndices()[i + 2]]);
	}
	ytransfrom += 1.0f;

	m_pRasterizer->EndDraw();
}