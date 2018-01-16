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
	void DrawVersionSelection();
	void DrawMeshProperties();
	void DrawLightProperties();
	void DrawAntiAliasingProperties();
	void Close() override;

	void SetTextSelectedColor();
	void SetTextDefaultColor();
	void SetTextTitleColor();

	void DrawAt(const std::string& p_text, uint16_t p_x, uint16_t p_y) const;

private:
	TTF_Font* m_font;
	Color m_textColor;
	SharedContext& m_sharedContext;

	std::string m_labelsVersions[8];
};
