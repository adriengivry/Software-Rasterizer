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
	void Draw() const;
	void Close() override;

	void DrawAt(std::string p_text, uint16_t p_x, uint16_t p_y, const uint8_t p_r = 255, const uint8_t p_g = 255, const uint8_t p_b = 255) const;

private:
	TTF_Font* m_font;
	SharedContext& m_sharedContext;
};
