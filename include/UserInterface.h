#pragma once
#include "IManager.h"
#include "SDL_ttf.h"
#include "SharedContext.h"

class UserInterface : public IManager
{
public:
	explicit UserInterface(SharedContext& p_sharedContext);
	~UserInterface();

	void Setup() override;
	void Update() override;
	void Draw();
	void DrawFPS();
	void DrawCameraParams();
	void DrawSceneInfo();
	void DrawVersionSelection();
	void DrawMeshProperties();
	void DrawLightProperties();
	void DrawAntiAliasingProperties();
	void DrawHelp();
	void DrawCredits();
	void DrawKonamiCode();
	void DrawZelda();
	void Close() override;

	void SetTextSelectedColor();
	void SetTextDefaultColor();
	void SetTextTitleColor();

	void DrawAt(const std::string& p_text, uint16_t p_x, uint16_t p_y, TTF_Font* p_font = nullptr) const;

private:
	TTF_Font* m_font;
	TTF_Font* m_smallFont;
	TTF_Font* m_pixelFont;
	Color m_textColor;
	SharedContext& m_sharedContext;

	std::string m_labelsVersions[8];
};
