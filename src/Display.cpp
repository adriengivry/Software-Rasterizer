#include "../include/Display.h"

using namespace Toolbox;

Display::Display() :
	m_pScene(nullptr),
	m_pEntity(nullptr),
	m_pLight(nullptr),
	m_pWindow(SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0)),
	m_pRenderer(SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED)),
	m_pTexture(SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT)),
	m_prTexture(new Texture(WINDOW_WIDTH, WINDOW_HEIGHT)),
	m_pRasterizer(*m_prTexture, *m_pRenderer, *m_pTexture),
	m_userInterface(new UserInterface(*m_pWindow, *m_pRenderer, m_sharedContext)),
	yturn(0)
{}

Display::~Display()
{
	SDL_DestroyTexture(m_pTexture);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	//delete m_pRasterizer;
	delete m_prTexture;
	delete m_pScene;
	for (int i = 0; i < 2; ++i)
	{
		delete m_pEntity[i];
	}
	delete m_pEntity;
	delete m_pLight;
}

void Display::Update()
{
	m_sharedContext.lastTime = m_sharedContext.currentTime;
	m_pRasterizer.Update();
	m_userInterface->Update();
	m_sharedContext.currentTime = SDL_GetTicks();
	m_sharedContext.deltaTime = (m_sharedContext.currentTime - m_sharedContext.lastTime) / 1000;
	m_sharedContext.fpsCounter = 1.f / m_sharedContext.deltaTime;
	if (SDL_GetTicks() / 1000 > 5.f)
	{
		m_sharedContext.fpsValues[m_sharedContext.fpsValuesBuffer++] = m_sharedContext.fpsCounter;
		if (m_sharedContext.fpsValuesBuffer > 100)
			m_sharedContext.fpsValuesBuffer = 0;

		uint16_t fpsSum = 0;
		uint8_t valuesCounter = 0;
		for (auto fpsValue : m_sharedContext.fpsValues)
		{
			if (fpsValue != 0)
			{
				fpsSum += fpsValue;
				++valuesCounter;
			}
		}

		m_sharedContext.averageFps = fpsSum / valuesCounter;
		m_sharedContext.minFps = m_sharedContext.fpsCounter < m_sharedContext.minFps ? m_sharedContext.fpsCounter : m_sharedContext.minFps;
		m_sharedContext.maxFps = m_sharedContext.fpsCounter > m_sharedContext.maxFps ? m_sharedContext.fpsCounter : m_sharedContext.maxFps;
	}
}

void Display::Init()
{
	//m_prTexture = new Texture(WINDOW_WIDTH, WINDOW_HEIGHT);
	//m_pWindow = SDL_CreateWindow("Rasterizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	//m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);
	//m_pTexture = SDL_CreateTexture(m_pRenderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);
	//m_pRasterizer = new Rasterizer(*m_prTexture, *m_pRenderer, *m_pTexture);
}

void Display::InitScene()
{
	m_pScene = new Scene();
	m_pLight = new Light(0, 0, 0);
	m_pEntity = new Entity*[2];
	for (int i = 0; i < 2; ++i)
	{
		m_pEntity[i] = new Entity();
	}
	m_pEntity[0]->SetMesh(*Mesh::CreateCube2());
	m_pScene->m_entities.push_back(m_pEntity[0]);
	//m_pScene->m_entities.push_back(m_pEntity[1]);
	m_pScene->m_lights.push_back(m_pLight);
}

void Display::RenderScene()
{
	Mat4 matrix = (Mat4::CreateTranslation(0, 0, -6) * Mat4::CreateRotation(45, yturn, 0));
	m_pScene->m_entities[0]->SetMatrix(matrix);
	m_pRasterizer.RenderScene3(m_pScene);
	yturn += m_sharedContext.deltaTime * 90;
}