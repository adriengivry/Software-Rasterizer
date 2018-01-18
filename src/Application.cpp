#include "Application.h"
#include <memory>

using namespace Toolbox;

Application::Application() :
	m_renderTexture(new Texture(Window::WIDTH, Window::HEIGHT)),
	m_rasterizer(*m_renderTexture, m_sharedContext),
	m_userInterface(new UserInterface(m_sharedContext)),
	m_eventManager(new EventManager(m_sharedContext))
{
	Application::Setup();
}

Application::~Application()
{
	Application::Close();
}

void Application::Setup()
{
	m_sharedContext.window = &m_window;
	m_sharedContext.scene = &m_scene;
	Init();
}

void Application::Close()
{
	delete m_eventManager;
	delete m_renderTexture;

	/*
	* TODO: WEIRD MEMORY ERROR NEED TO BE CORRECTED (Memory leak if this part is commented)
	* delete m_userInterface;
	*/
}

void Application::Update()
{
	m_sharedContext.appInfos.lastTime = m_sharedContext.appInfos.currentTime;

	UpdateMeshTexture();
	UpdateMeshColor();
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

void Application::Draw() const
{
	SDL_RenderClear(m_window.GetRenderer());
	m_rasterizer.Draw();
	m_userInterface->Draw();
	SDL_RenderPresent(m_window.GetRenderer());
}

void Application::Init()
{
	m_scene.InitMeshes(m_sharedContext.appInfos.selectedVersion, m_sharedContext.appInfos.meshMode);
	m_scene.InitEntities(m_sharedContext.appInfos.selectedVersion, m_sharedContext.appInfos.meshMode);
	m_scene.InitLights();
}

void Application::RenderScene()
{
	const Mat4 matrix = 
		Mat4::CreateTranslation(m_sharedContext.appInfos.cameraParams.xOffset, m_sharedContext.appInfos.cameraParams.yOffset, 0).CreateInverse() *
		Mat4::CreateTranslation(0 , 0, m_sharedContext.appInfos.cameraParams.zoomOffset) *
		Mat4::CreateRotation(m_sharedContext.appInfos.cameraParams.xRotationOffset, m_sharedContext.appInfos.cameraParams.yRotationOffset, 0);

	m_sharedContext.appInfos.secondCubeRotationOffset += 20 * m_sharedContext.appInfos.deltaTime;

	const Mat4 matrix2 =
		Mat4::CreateTranslation(0, 0, 0).CreateInverse() *
		Mat4::CreateTranslation(0, 0, -6) *
		Mat4::CreateRotation(m_sharedContext.appInfos.secondCubeRotationOffset, m_sharedContext.appInfos.secondCubeRotationOffset, 0) *
		Mat4::CreateScale(1.5f, 1.5f, 1.5f);

	const Mat4 matrix3 =
		Mat4::CreateTranslation(m_sharedContext.appInfos.cameraParams.xOffset, m_sharedContext.appInfos.cameraParams.yOffset, 0).CreateInverse() *
		Mat4::CreateTranslation(0, 0, m_sharedContext.appInfos.cameraParams.zoomOffset);

	if (m_sharedContext.appInfos.selectedVersion < 5)
	{
		m_scene.entities[0]->SetMatrix(matrix);
	}

	if (m_sharedContext.appInfos.selectedVersion == 5)
	{
		m_scene.entities[0]->SetMatrix(matrix);
	}

	if (m_sharedContext.appInfos.selectedVersion == 6)
	{
		m_scene.entities[0]->SetMatrix(matrix2);
		m_scene.entities[1]->SetMatrix(matrix);
	}

	if (m_sharedContext.appInfos.selectedVersion == 7)
	{
		m_scene.entities[0]->SetMatrix(matrix3);
	}

	m_sharedContext.appInfos.polygons = 0;

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
	case 7:
		m_rasterizer.RenderAntialiasing(&m_scene);
		break;
	}
}

void Application::UpdateCamera()
{
	float xOffset = 0;
	float yOffset = 0;
	float zoomOffset = 0;
	float xRotationOffset = 0;
	float yRotationOffset = 0;

	if (m_sharedContext.actions.moveLeft)
		xOffset -= 2;
	if (m_sharedContext.actions.moveRight)
		xOffset += 2;
	if (m_sharedContext.actions.moveUp)
		yOffset += 2;
	if (m_sharedContext.actions.moveDown)
		yOffset -= 2;

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

	// Update camera params
	m_sharedContext.appInfos.cameraParams.xOffset += xOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.yOffset += yOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.zoomOffset += zoomOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.xRotationOffset += xRotationOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.yRotationOffset += yRotationOffset * m_sharedContext.appInfos.deltaTime;

	// Keep rotation between 0 and 360
	while (m_sharedContext.appInfos.cameraParams.xRotationOffset >= 360) m_sharedContext.appInfos.cameraParams.xRotationOffset -= 360;
	while (m_sharedContext.appInfos.cameraParams.yRotationOffset >= 360) m_sharedContext.appInfos.cameraParams.yRotationOffset -= 360;
	while (m_sharedContext.appInfos.cameraParams.xRotationOffset < 0) m_sharedContext.appInfos.cameraParams.xRotationOffset += 360;
	while (m_sharedContext.appInfos.cameraParams.yRotationOffset < 0) m_sharedContext.appInfos.cameraParams.yRotationOffset += 360;

	// Prevent zooming or de-zooming too much
	if (m_sharedContext.appInfos.selectedVersion != 7)
	{
		if (m_sharedContext.appInfos.cameraParams.zoomOffset >= -3) m_sharedContext.appInfos.cameraParams.zoomOffset = -3;
		if (m_sharedContext.appInfos.cameraParams.zoomOffset <= -40) m_sharedContext.appInfos.cameraParams.zoomOffset = -40;
	}
	else
	{
		if (m_sharedContext.appInfos.cameraParams.zoomOffset >= -1) m_sharedContext.appInfos.cameraParams.zoomOffset = -1;
		if (m_sharedContext.appInfos.cameraParams.zoomOffset <= -40) m_sharedContext.appInfos.cameraParams.zoomOffset = -40;
	}
}

void Application::UpdateLights()
{
	if (m_sharedContext.appInfos.selectedVersion == 2 || m_sharedContext.appInfos.selectedVersion == 3)
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
}

void Application::UpdateMeshColor()
{
	if (m_sharedContext.appInfos.selectedVersion < 5)
	{
		float redOffset = 0;
		float greenOffset = 0;
		float blueOffset = 0;
		const float colorIncrementPerSecond = 50;

		if (m_sharedContext.actions.addRed)
			redOffset += colorIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		if (m_sharedContext.actions.addGreen)
			greenOffset += colorIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		if (m_sharedContext.actions.addBlue)
			blueOffset += colorIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		m_sharedContext.appInfos.cubeParams.red += redOffset;
		while (m_sharedContext.appInfos.cubeParams.red > 255.f) m_sharedContext.appInfos.cubeParams.red /= 255;

		m_sharedContext.appInfos.cubeParams.green += greenOffset;
		while (m_sharedContext.appInfos.cubeParams.green > 255.f) m_sharedContext.appInfos.cubeParams.green /= 255;

		m_sharedContext.appInfos.cubeParams.blue += blueOffset;
		while (m_sharedContext.appInfos.cubeParams.blue > 255.f) m_sharedContext.appInfos.cubeParams.blue /= 255;

		m_scene.entities[0]->SetColor(m_sharedContext.appInfos.cubeParams.red, m_sharedContext.appInfos.cubeParams.green, m_sharedContext.appInfos.cubeParams.blue);
	}

	if (m_sharedContext.appInfos.selectedVersion == 6)
	{
		float transparencyOffset = 0;
		const float transparencyIncrementPerSecond = 20;

		if (m_sharedContext.actions.addTransparency)
			transparencyOffset += transparencyIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		m_sharedContext.appInfos.cubeParams.transparency += transparencyOffset;
		while (m_sharedContext.appInfos.cubeParams.transparency > 100) m_sharedContext.appInfos.cubeParams.transparency /= 100;

		m_scene.entities[1]->SetAlpha(m_sharedContext.appInfos.cubeParams.transparency / 100.f);
	}
}

void Application::UpdateMeshTexture() const
{
	if (m_sharedContext.appInfos.selectedVersion == 5)
		m_sharedContext.scene->entities[0]->GetMesh()->SetImage(m_sharedContext.scene->textures[m_sharedContext.appInfos.cubeParams.imageID]);
	else if (m_sharedContext.appInfos.selectedVersion == 6)
		m_sharedContext.scene->entities[1]->GetMesh()->SetImage(m_sharedContext.scene->textures[m_sharedContext.appInfos.cubeParams.imageID]);
}

SharedContext& Application::GetContext()
{
	return m_sharedContext;
}
