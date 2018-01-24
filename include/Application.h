#pragma once
#include "Rasterizer.h"
#include "UserInterface.h"
#include <numeric>
#include "EventManager.h"
#include "irrKlang.h"

class Application : public IManager
{
public:
	Application();
	~Application();
	void Setup() override;
	void Close() override;
	void Update() override;
	void Draw() const;
	void Init();
	void RenderScene();
	void UpdateMatrices();
	void UpdateCamera();
	void UpdateRealCamera();
	void UpdateLights();
	void UpdateMeshColor();
	void UpdateMeshTexture() const;
	void UpdateAASelection();
	void UpdateFPSCount();

	void UpdateAntialiasingMatrix();
	void UpdateAlphaBlendingAnimation();
	void UpdateZeldaAnimation();

	void UpdatePolygonCount();

	SharedContext& GetContext();
private:
	Scene m_scene;
	Texture* m_renderTexture;
	SharedContext m_sharedContext;
	Rasterizer m_rasterizer;
	UserInterface* m_userInterface;
	EventManager* m_eventManager;
	Window m_window;
	Toolbox::Mat4 m_defaultCameraMatrix;
	Toolbox::Mat4 m_realCameraMatrix;
	Toolbox::Mat4 m_antialiasingCameraMatrix;
	Toolbox::Mat4 m_alphablendingAnimationMatrix;
	irrklang::ISoundEngine* m_soundEngine;
};