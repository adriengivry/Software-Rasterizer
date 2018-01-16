#pragma once
#include "Rasterizer.h"
#include "UserInterface.h"
#include <numeric>
#include "EventManager.h"

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
	void UpdateCamera();
	void UpdateLights();
	void UpdateCubeColor();

	SharedContext& GetContext();
private:
	Scene m_scene;
	Texture* m_renderTexture;
	SharedContext m_sharedContext;
	Rasterizer m_rasterizer;
	UserInterface* m_userInterface;
	EventManager* m_eventManager;
	Image* m_image;
	Image* m_image2;
	Window m_window;
};
