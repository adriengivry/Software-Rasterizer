#include "Application.h"

using namespace Toolbox;

Application::Application() :
	m_renderTexture(new Texture(Window::WIDTH, Window::HEIGHT)),
	m_rasterizer(*m_renderTexture, m_sharedContext),
	m_userInterface(new UserInterface(m_sharedContext)),
	m_eventManager(new EventManager(m_sharedContext)),
	m_image(nullptr)
{
	m_sharedContext.window = &m_window;
	Init();
}

Application::~Application()
{
	delete m_eventManager;
	delete m_renderTexture;
	delete m_image;

	/*
	 * TODO: WEIRD MEMORY ERROR NEED TO BE CORRECTED (Memory leak if this part is commented)
	 * delete m_userInterface;
	*/
}

void Application::Update()
{
	m_sharedContext.appInfos.lastTime = m_sharedContext.appInfos.currentTime;

	UpdateCamera();
	UpdateLights();
	RenderScene();
	m_eventManager->Update();
	m_rasterizer.Update();
	m_userInterface->Update();

	m_sharedContext.appInfos.currentTime = SDL_GetTicks();
	m_sharedContext.appInfos.deltaTime = (m_sharedContext.appInfos.currentTime - m_sharedContext.appInfos.lastTime) / 1000;
	m_sharedContext.appInfos.fpsCounter = 1.f / m_sharedContext.appInfos.deltaTime;

	m_sharedContext.appInfos.fpsValues[m_sharedContext.appInfos.fpsValuesBuffer] = m_sharedContext.appInfos.fpsCounter;

	uint16_t fpsSum = 0;

	if (m_sharedContext.appInfos.fpsValuesBuffer == 9)
	{
		uint16_t minFps = m_sharedContext.appInfos.fpsValues[0];
		uint16_t maxFps = m_sharedContext.appInfos.fpsValues[0];
		for (auto fpsValue : m_sharedContext.appInfos.fpsValues)
		{
			fpsSum += fpsValue;
			if (fpsValue > maxFps)
				maxFps = fpsValue;
			if (fpsValue < minFps)
				minFps = fpsValue;
		}
		m_sharedContext.appInfos.averageFps = fpsSum / 10;
		m_sharedContext.appInfos.minFps = minFps;
		m_sharedContext.appInfos.maxFps = maxFps;
		m_sharedContext.appInfos.fpsValuesBuffer = 0;
	}
	else
		++m_sharedContext.appInfos.fpsValuesBuffer;
}

void Application::Draw()
{
	SDL_RenderClear(m_window.GetRenderer());
	m_rasterizer.Draw();
	m_userInterface->Draw();
	SDL_RenderPresent(m_window.GetRenderer());
}

void Application::Init()
{
	SDL_SetRenderDrawBlendMode(m_window.GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(m_window.GetTexture(), SDL_BLENDMODE_BLEND);
	m_image = new Image("../assets/texture.png");
	m_scene.InitEntities();
	m_scene.InitLights();
	m_scene.entities[1]->GetMesh()->SetImage(m_image);
	m_scene.entities[2]->GetMesh()->SetImage(m_image);
	m_scene.entities[1]->SetAlpha(0.4f);
	m_scene.entities[2]->SetAlpha(1.0f);
}

void Application::RenderScene()
{
	const Mat4 matrix = 
		Mat4::CreateTranslation(m_cameraParams.xOffset, 0, 0).CreateInverse() * 
		Mat4::CreateTranslation(0 , 0, -6 + m_cameraParams.zoomOffset) * 
		Mat4::CreateRotation(45 + m_cameraParams.xRotationOffset, 45 + m_cameraParams.yRotationOffset, 0);

	const Mat4 matrix2 =
		Mat4::CreateTranslation(m_cameraParams.xOffset, 0, 0).CreateInverse() *
		Mat4::CreateTranslation(0, 0, -6 + m_cameraParams.zoomOffset) *
		Mat4::CreateRotation(45, 45, 0) *
		Mat4::CreateScale(2.f, 2.f, 2.f);
	m_scene.entities[0]->SetMatrix(matrix);
	m_scene.entities[1]->SetMatrix(matrix);
	m_scene.entities[2]->SetMatrix(matrix2);
	switch (m_sharedContext.appInfos.selectedVersion)
	{
	default:
		break;
	case 1:
		m_rasterizer.RenderScene(&m_scene);
		break;
	case 2:
		m_rasterizer.RenderScenePhong(&m_scene);
		break;
	case 3:
		m_rasterizer.RenderSceneBlinnPhong(&m_scene);
		break;
	case 4:
		m_rasterizer.RenderSceneWireframe(&m_scene);
		break;
	case 5:
		m_rasterizer.RenderTexture(&m_scene);
		break;
	case 6:
		m_rasterizer.RenderAlphaBlending(&m_scene);
		break;
	}
}

void Application::UpdateCamera()
{
	float xOffset = 0;
	float zoomOffset = 0;
	float xRotationOffset = 0;
	float yRotationOffset = 0;

	if (m_sharedContext.actions.moveLeft)
		xOffset -= 2;
	if (m_sharedContext.actions.moveRight)
		xOffset += 2;

	if (m_sharedContext.actions.zoomIn)
		zoomOffset += 5;
	if (m_sharedContext.actions.zoomOut)
		zoomOffset -= 5;

	if (m_sharedContext.actions.xTurnClockwise)
		xRotationOffset += 90;
	if (m_sharedContext.actions.xTurnCounterClockwise)
		xRotationOffset -= 90;
	if (m_sharedContext.actions.yTurnClockwise)
		yRotationOffset += 90;
	if (m_sharedContext.actions.yTurnCounterClockwise)
		yRotationOffset -= 90;

	m_cameraParams.xOffset += xOffset * m_sharedContext.appInfos.deltaTime;
	m_cameraParams.zoomOffset += zoomOffset * m_sharedContext.appInfos.deltaTime;
	m_cameraParams.xRotationOffset += xRotationOffset * m_sharedContext.appInfos.deltaTime;
	m_cameraParams.yRotationOffset += yRotationOffset * m_sharedContext.appInfos.deltaTime;

	if (m_cameraParams.zoomOffset >= 4) m_cameraParams.zoomOffset = 4;
	if (m_cameraParams.zoomOffset <= -15) m_cameraParams.zoomOffset = -15;
}

void Application::UpdateLights()
{
	float lightOffset = 0;

	const float lightIncrementPerSecond = 20;

	if (m_sharedContext.actions.increaseLight)
		lightOffset += lightIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

	if (m_sharedContext.actions.decreaseLight)
		lightOffset -= lightIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

	switch (m_sharedContext.appInfos.selectedLight)
	{
	default: 
		break;
	case AMBIANT:
		m_sharedContext.appInfos.lightParams.ambiant += lightOffset;
		break;
	case DIFFUSE:
		m_sharedContext.appInfos.lightParams.diffuse += lightOffset;
		break;
	case SPECULAR:
		m_sharedContext.appInfos.lightParams.specular += lightOffset;
		break;
	}

	if (m_sharedContext.appInfos.lightParams.ambiant < 0)
		m_sharedContext.appInfos.lightParams.ambiant = 0;
	else if (m_sharedContext.appInfos.lightParams.ambiant > 100)
		m_sharedContext.appInfos.lightParams.ambiant = 100;

	if (m_sharedContext.appInfos.lightParams.diffuse < 0)
		m_sharedContext.appInfos.lightParams.diffuse = 0;
	else if (m_sharedContext.appInfos.lightParams.diffuse > 100)
		m_sharedContext.appInfos.lightParams.diffuse = 100;

	if (m_sharedContext.appInfos.lightParams.specular < 0)
		m_sharedContext.appInfos.lightParams.specular = 0;
	else if (m_sharedContext.appInfos.lightParams.specular > 100)
		m_sharedContext.appInfos.lightParams.specular = 100;
}

SharedContext& Application::GetContext()
{
	return m_sharedContext;
}
