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
	m_soundEngine = irrklang::createIrrKlangDevice();
	m_sharedContext.soundEngine = m_soundEngine;
	m_sharedContext.window = &m_window;
	m_sharedContext.scene = &m_scene;
	Init();
}

void Application::Close()
{
	delete m_eventManager;
	delete m_renderTexture;

	m_soundEngine->drop();

	/*
	* TODO: WEIRD MEMORY ERROR NEED TO BE CORRECTED (Memory leak if this part is commented)
	* delete m_userInterface;
	*/
}

void Application::Update()
{
	m_sharedContext.appInfos.lastTime = m_sharedContext.appInfos.currentTime;

	const uint8_t& selectedVersion = m_sharedContext.appInfos.selectedVersion;

	if (selectedVersion == 0)													UpdateZeldaAnimation();
	if (selectedVersion == 6)													UpdateAlphaBlendingAnimation();
	if (selectedVersion != 8)													UpdateCamera();
	if (selectedVersion == 8)													UpdateRealCamera();
	if (selectedVersion >= 1 && selectedVersion <= 3)							UpdateAASelection();
	if (selectedVersion == 5 || selectedVersion == 6)							UpdateMeshTexture();
	if (selectedVersion == 2 || selectedVersion == 3)							UpdateLights();
	if (selectedVersion != 0 && (selectedVersion < 5 || selectedVersion >= 6))	UpdateMeshColor();
	
	if (m_sharedContext.appInfos.selectedVersion != 0)
		m_sharedContext.appInfos.previousSelectedVersion = m_sharedContext.appInfos.selectedVersion;

	UpdateMatrices();
	UpdatePolygonCount();
	RenderScene();

	m_eventManager->Update();
	m_rasterizer.Update();
	m_userInterface->Update();

	UpdateFPSCount();
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
	switch (m_sharedContext.appInfos.selectedVersion)
	{
		default:												break;
		case 1: m_rasterizer.RenderScene(&m_scene);				break;
		case 2: m_rasterizer.RenderScenePhong(&m_scene);		break;
		case 3: m_rasterizer.RenderSceneBlinnPhong(&m_scene);	break;
		case 4: m_rasterizer.RenderSceneWireframe(&m_scene);	break;
		case 5: m_rasterizer.RenderTexture(&m_scene);			break;
		case 6: m_rasterizer.RenderAlphaBlending(&m_scene);		break;
		case 7: m_rasterizer.RenderAntialiasing(&m_scene);		break;
		case 8: m_rasterizer.RenderRealCameraScene(&m_scene, m_realCameraMatrix); break;
		case 0: m_rasterizer.RenderZelda(&m_scene);				break;
	}
}

void Application::UpdateMatrices()
{
	switch (m_sharedContext.appInfos.selectedVersion)
	{
		default:	m_scene.entities[0]->SetMatrix(m_defaultCameraMatrix);			break;
		case 0:																		break;
		case 5:		m_scene.entities[0]->SetMatrix(m_defaultCameraMatrix);			break;
		case 7:		m_scene.entities[0]->SetMatrix(m_antialiasingCameraMatrix);		break;
		case 6:		m_scene.entities[0]->SetMatrix(m_alphablendingAnimationMatrix);
					m_scene.entities[1]->SetMatrix(m_defaultCameraMatrix);			break;
		case 8:		m_scene.entities[0]->SetMatrix(Mat4::CreateTranslation(0, 0, 0) * Mat4::CreateRotation(0, 0, 0));															
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
	float zRotationOffset = 0;

	if (m_sharedContext.actions.moveLeft)	xOffset -= 2;
	if (m_sharedContext.actions.moveRight)	xOffset += 2;
	if (m_sharedContext.actions.moveUp)		yOffset += 2;
	if (m_sharedContext.actions.moveDown)	yOffset -= 2;

	if (m_sharedContext.actions.zoomIn)		zoomOffset += 2;
	if (m_sharedContext.actions.zoomOut)	zoomOffset -= 2;

	if (m_sharedContext.actions.xTurnClockwise)			xRotationOffset += 90;
	if (m_sharedContext.actions.xTurnCounterClockwise)	xRotationOffset -= 90;
	if (m_sharedContext.actions.yTurnClockwise)			yRotationOffset += 90;
	if (m_sharedContext.actions.yTurnCounterClockwise)	yRotationOffset -= 90;
	if (m_sharedContext.actions.zTurnClockwise)			zRotationOffset += 90;
	if (m_sharedContext.actions.zTurnCounterClockwise)	zRotationOffset -= 90;

	// Update camera params
	m_sharedContext.appInfos.cameraParams.xOffset += xOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.yOffset += yOffset * m_sharedContext.appInfos.deltaTime;
	m_sharedContext.appInfos.cameraParams.zoomOffset += zoomOffset * m_sharedContext.appInfos.deltaTime;

	// Rotation disabled in AA version
	if (m_sharedContext.appInfos.selectedVersion != 7)
	{
		m_sharedContext.appInfos.cameraParams.xRotationOffset += xRotationOffset * m_sharedContext.appInfos.deltaTime;
		m_sharedContext.appInfos.cameraParams.yRotationOffset += yRotationOffset * m_sharedContext.appInfos.deltaTime;
	}
	else
	{
		m_sharedContext.appInfos.cameraParams.zRotationOffset += zRotationOffset * m_sharedContext.appInfos.deltaTime;
	}

	// Keep rotation between 0 and 360
	while (m_sharedContext.appInfos.cameraParams.xRotationOffset >= 360) m_sharedContext.appInfos.cameraParams.xRotationOffset -= 360;
	while (m_sharedContext.appInfos.cameraParams.yRotationOffset >= 360) m_sharedContext.appInfos.cameraParams.yRotationOffset -= 360;
	while (m_sharedContext.appInfos.cameraParams.zRotationOffset >= 360) m_sharedContext.appInfos.cameraParams.zRotationOffset -= 360;
	while (m_sharedContext.appInfos.cameraParams.xRotationOffset < 0) m_sharedContext.appInfos.cameraParams.xRotationOffset += 360;
	while (m_sharedContext.appInfos.cameraParams.yRotationOffset < 0) m_sharedContext.appInfos.cameraParams.yRotationOffset += 360;
	while (m_sharedContext.appInfos.cameraParams.zRotationOffset < 0) m_sharedContext.appInfos.cameraParams.zRotationOffset += 360;

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

	if (m_sharedContext.appInfos.selectedVersion < 7)
	{
		m_defaultCameraMatrix =
			Mat4::CreateTranslation(m_sharedContext.appInfos.cameraParams.xOffset, m_sharedContext.appInfos.cameraParams.yOffset, 0).CreateInverse() *
			Mat4::CreateTranslation(0, 0, m_sharedContext.appInfos.cameraParams.zoomOffset) *
			Mat4::CreateRotation(m_sharedContext.appInfos.cameraParams.xRotationOffset, m_sharedContext.appInfos.cameraParams.yRotationOffset, 0);
	}

	if (m_sharedContext.appInfos.selectedVersion == 7)
	{
		m_antialiasingCameraMatrix =
			Mat4::CreateTranslation(m_sharedContext.appInfos.cameraParams.xOffset, m_sharedContext.appInfos.cameraParams.yOffset, 0).CreateInverse() *
			Mat4::CreateTranslation(0, 0, m_sharedContext.appInfos.cameraParams.zoomOffset) *
			Mat4::CreateRotation(0, 0, m_sharedContext.appInfos.cameraParams.zRotationOffset);
	}
}

void Application::UpdateRealCamera()
{
	float pitch = 0;
	//float yaw = 0;
	float angleAroundPlayer = 0;
	float distance = 0;
	float theta = 0;
	float offsetX = 0;
	float offsetZ = 0;
	if (m_sharedContext.actions.zoomIn) distance -= 1.0f;
	if (m_sharedContext.actions.zoomOut) distance += 1.0f;

	m_sharedContext.appInfos.realCameraParams.distanceFromObject += distance;

	if (m_sharedContext.actions.xTurnClockwise) pitch -= 1.0f;
	if (m_sharedContext.actions.xTurnCounterClockwise) pitch += 1.0f;

	m_sharedContext.appInfos.realCameraParams.pitch += pitch;

	if (m_sharedContext.actions.yTurnClockwise) angleAroundPlayer -= 1.0f;
	if (m_sharedContext.actions.yTurnCounterClockwise) angleAroundPlayer += 1.0f;

	m_sharedContext.appInfos.realCameraParams.angleAroundPlayer += angleAroundPlayer;

	m_sharedContext.appInfos.realCameraParams.horizontalDistance = m_sharedContext.appInfos.realCameraParams.distanceFromObject * cos(m_sharedContext.appInfos.realCameraParams.pitch * DEG_TO_RAD);
	m_sharedContext.appInfos.realCameraParams.verticalDistance = m_sharedContext.appInfos.realCameraParams.distanceFromObject * sin(m_sharedContext.appInfos.realCameraParams.pitch * DEG_TO_RAD);

	m_sharedContext.appInfos.realCameraParams.cameraY = m_sharedContext.appInfos.realCameraParams.verticalDistance;
	theta = m_sharedContext.appInfos.realCameraParams.angleAroundPlayer;
	offsetX = m_sharedContext.appInfos.realCameraParams.horizontalDistance * sin(theta * DEG_TO_RAD);
	offsetZ = m_sharedContext.appInfos.realCameraParams.horizontalDistance * cos(theta * DEG_TO_RAD);

	m_sharedContext.appInfos.realCameraParams.cameraX = -offsetX;
	m_sharedContext.appInfos.realCameraParams.cameraZ = -offsetZ;
	m_sharedContext.appInfos.realCameraParams.yaw = 180 - m_sharedContext.appInfos.realCameraParams.angleAroundPlayer;
	m_realCameraMatrix = Mat4::CreateView(m_sharedContext.appInfos.realCameraParams.cameraX, m_sharedContext.appInfos.realCameraParams.cameraY, m_sharedContext.appInfos.realCameraParams.cameraZ, 0, 0, 0, 0, 1, 0);
}

void Application::UpdateLights()
{
	if (m_sharedContext.appInfos.selectedVersion >= 2 || m_sharedContext.appInfos.selectedVersion <= 3)
	{
		float ambiantOffset = 0;
		float diffuseOffset = 0;
		float specularOffset = 0;
		const float lightIncrementPerSecond = 15;

		if (m_sharedContext.actions.addAmbiant)
			ambiantOffset += lightIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		if (m_sharedContext.actions.addDiffuse)
			diffuseOffset += lightIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		if (m_sharedContext.actions.addSpecular)
			specularOffset += lightIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		m_sharedContext.appInfos.lightParams.ambiant += ambiantOffset;
		while (m_sharedContext.appInfos.lightParams.ambiant > 100.f) m_sharedContext.appInfos.lightParams.ambiant /= 100;

		m_sharedContext.appInfos.lightParams.diffuse += diffuseOffset;
		while (m_sharedContext.appInfos.lightParams.diffuse > 100.f) m_sharedContext.appInfos.lightParams.diffuse /= 100;

		m_sharedContext.appInfos.lightParams.specular += specularOffset;
		while (m_sharedContext.appInfos.lightParams.specular > 100.f) m_sharedContext.appInfos.lightParams.specular /= 100;
	}
}

void Application::UpdateMeshColor()
{
	if (m_sharedContext.appInfos.selectedVersion < 5 || m_sharedContext.appInfos.selectedVersion >= 7)
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

		m_sharedContext.appInfos.meshParams.red += redOffset;
		while (m_sharedContext.appInfos.meshParams.red > 255.f) m_sharedContext.appInfos.meshParams.red /= 255;

		m_sharedContext.appInfos.meshParams.green += greenOffset;
		while (m_sharedContext.appInfos.meshParams.green > 255.f) m_sharedContext.appInfos.meshParams.green /= 255;

		m_sharedContext.appInfos.meshParams.blue += blueOffset;
		while (m_sharedContext.appInfos.meshParams.blue > 255.f) m_sharedContext.appInfos.meshParams.blue /= 255;

		m_scene.entities[0]->SetColor(m_sharedContext.appInfos.meshParams.red, m_sharedContext.appInfos.meshParams.green, m_sharedContext.appInfos.meshParams.blue);
	}

	if (m_sharedContext.appInfos.selectedVersion == 6)
	{
		float transparencyOffset = 0;
		const float transparencyIncrementPerSecond = 20;

		if (m_sharedContext.actions.addTransparency)
			transparencyOffset += transparencyIncrementPerSecond * m_sharedContext.appInfos.deltaTime;

		m_sharedContext.appInfos.meshParams.transparency += transparencyOffset;
		while (m_sharedContext.appInfos.meshParams.transparency > 100) m_sharedContext.appInfos.meshParams.transparency /= 100;

		m_scene.entities[1]->SetAlpha(m_sharedContext.appInfos.meshParams.transparency / 100.f);
	}
}

void Application::UpdateMeshTexture() const
{
	uint8_t entityIDToBindTheTextureOn = 0;
	if (m_sharedContext.appInfos.selectedVersion == 6)
		entityIDToBindTheTextureOn = 1;

	const uint8_t& imageID = m_sharedContext.appInfos.meshMode == CUBE ? m_sharedContext.appInfos.meshParams.cubeImageID : m_sharedContext.appInfos.meshParams.sphereImageID;
	std::vector<Image*>& textureContainer = m_sharedContext.appInfos.meshMode == CUBE ? m_sharedContext.scene->cubeTextures : m_sharedContext.scene->sphereTextures;

	m_sharedContext.scene->entities[entityIDToBindTheTextureOn]->GetMesh()->SetImage(textureContainer[imageID]);
}

void Application::UpdateAASelection()
{
	if (m_sharedContext.appInfos.selectedAA != 0 && m_sharedContext.appInfos.selectedAA != 3)
		m_sharedContext.appInfos.selectedAA = 3;
}

void Application::UpdateFPSCount()
{
	m_sharedContext.appInfos.currentTime = static_cast<float>(SDL_GetTicks());
	m_sharedContext.appInfos.deltaTime = (m_sharedContext.appInfos.currentTime - m_sharedContext.appInfos.lastTime) / 1000;
	m_sharedContext.appInfos.fpsCounter = static_cast<uint16_t>(1.f / m_sharedContext.appInfos.deltaTime);

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

void Application::UpdateAntialiasingMatrix()
{
	m_scene.entities[0]->SetMatrix(m_antialiasingCameraMatrix);
}

void Application::UpdateAlphaBlendingAnimation()
{
	m_sharedContext.appInfos.secondCubeRotationOffset += 20 * m_sharedContext.appInfos.deltaTime;
	m_alphablendingAnimationMatrix =
		Mat4::CreateTranslation(0, 0, -6) *
		Mat4::CreateRotation(m_sharedContext.appInfos.secondCubeRotationOffset, m_sharedContext.appInfos.secondCubeRotationOffset, 0) *
		Mat4::CreateScale(1.5f, 1.5f, 1.5f);
}

void Application::UpdateZeldaAnimation()
{
	Zelda& zelda = m_sharedContext.appInfos.zelda;
	zelda.timer += m_sharedContext.appInfos.deltaTime;

	if (zelda.timer >= 1.5f && !zelda.soundPlayed)
	{
		m_sharedContext.soundEngine->play2D("../assets/sounds/zelda.wav");
		zelda.soundPlayed = true;
	}

	if (zelda.timer >= 18.f)
	{
		m_sharedContext.appInfos.selectedVersion = m_sharedContext.appInfos.previousSelectedVersion;
		m_sharedContext.RefreshScene();
	}

	zelda.mat4_x += Zelda::xTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat4_y += Zelda::yTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat4_z += Zelda::zTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat5_x -= Zelda::xTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat5_y += Zelda::yTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat5_z += Zelda::zTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat6_y -= Zelda::yTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat6_z += Zelda::zTranslationSpeed * m_sharedContext.appInfos.deltaTime;

	if (zelda.timer >= 8.f)
	{
		m_scene.entities[3]->GetMesh()->SetImage(m_scene.zeldaImage);
		zelda.mat7_z += Zelda::titleTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	}

	if (zelda.timer >= 10.f)
	{
		m_scene.entities[4]->GetMesh()->SetImage(m_scene.background);
		zelda.mat8_y += Zelda::backgroundTranslationSpeed * m_sharedContext.appInfos.deltaTime;
	}

	zelda.mat4_x_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat4_y_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat5_x_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat5_y_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat6_x_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;
	zelda.mat6_y_rotation += Zelda::rotationSpeed * m_sharedContext.appInfos.deltaTime;

	if (zelda.mat4_x > Zelda::mat4dest_x) zelda.mat4_x = Zelda::mat4dest_x;
	if (zelda.mat4_y > Zelda::mat4dest_y) zelda.mat4_y = Zelda::mat4dest_y;
	if (zelda.mat4_z > Zelda::mat4dest_z) zelda.mat4_z = Zelda::mat4dest_z;
	if (zelda.mat5_x < Zelda::mat5dest_x) zelda.mat5_x = Zelda::mat5dest_x;
	if (zelda.mat5_y > Zelda::mat5dest_y) zelda.mat5_y = Zelda::mat5dest_y;
	if (zelda.mat5_z > Zelda::mat5dest_z) zelda.mat5_z = Zelda::mat5dest_z;
	if (zelda.mat6_y < Zelda::mat6dest_y) zelda.mat6_y = Zelda::mat6dest_y;
	if (zelda.mat6_z > Zelda::mat6dest_z) zelda.mat6_z = Zelda::mat6dest_z;
	if (zelda.mat7_z > Zelda::mat7dest_z) zelda.mat7_z = Zelda::mat7dest_z;
	if (zelda.mat8_y > Zelda::mat8dest_y) zelda.mat8_y = Zelda::mat8dest_y;	

	if (zelda.mat4_x_rotation > Zelda::xMaxRotations * 360) zelda.mat4_x_rotation = Zelda::xMaxRotations * 360;
	if (zelda.mat4_y_rotation > Zelda::yMaxRotations * 360) zelda.mat4_y_rotation = Zelda::yMaxRotations * 360;
	if (zelda.mat5_x_rotation > Zelda::xMaxRotations * 360) zelda.mat5_x_rotation = Zelda::xMaxRotations * 360;
	if (zelda.mat5_y_rotation > Zelda::yMaxRotations * 360) zelda.mat5_y_rotation = Zelda::yMaxRotations * 360;
	if (zelda.mat6_x_rotation > Zelda::xMaxRotations * 360) zelda.mat6_x_rotation = Zelda::xMaxRotations * 360;
	if (zelda.mat6_y_rotation > Zelda::yMaxRotations * 360) zelda.mat6_y_rotation = Zelda::yMaxRotations * 360;

	const Mat4 matrix4 =
		Mat4::CreateTranslation(zelda.mat4_x, zelda.mat4_y, zelda.mat4_z) *
		Mat4::CreateRotation(zelda.mat4_x_rotation, zelda.mat4_y_rotation, 0);

	const Mat4 matrix5 =
		Mat4::CreateTranslation(zelda.mat5_x, zelda.mat5_y, zelda.mat5_z) *
		Mat4::CreateRotation(zelda.mat5_x_rotation, zelda.mat5_y_rotation, 0);

	const Mat4 matrix6 =
		Mat4::CreateTranslation(zelda.mat6_x, zelda.mat6_y, zelda.mat6_z) *
		Mat4::CreateRotation(zelda.mat6_x_rotation, zelda.mat6_y_rotation, 0);

	const Mat4 matrix7 =
		Mat4::CreateTranslation(0, 0, zelda.mat7_z) *
		Mat4::CreateRotation(0, 0, 180) *
		Mat4::CreateScale(11, 7, 0.2f);

	const Mat4 matrix8 =
		Mat4::CreateTranslation(0, zelda.mat8_y, -10) *
		Mat4::CreateRotation(0, 0, 180) *
		Mat4::CreateScale(11, 7, 0.2f);

	m_scene.entities[0]->SetMatrix(matrix4);
	m_scene.entities[1]->SetMatrix(matrix5);
	m_scene.entities[2]->SetMatrix(matrix6);
	m_scene.entities[3]->SetMatrix(matrix7);
	m_scene.entities[4]->SetMatrix(matrix8);
}

void Application::UpdatePolygonCount()
{
	m_sharedContext.appInfos.polygons = 0;
	for (auto & entitie : m_sharedContext.scene->entities)
		m_sharedContext.appInfos.polygons += static_cast<uint16_t>(entitie->GetMesh()->GetIndices().size());
	m_sharedContext.appInfos.polygons /= 3;
}

SharedContext& Application::GetContext()
{
	return m_sharedContext;
}
