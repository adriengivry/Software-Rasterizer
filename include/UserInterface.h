#pragma once
#include "IManager.h"
#include "SDL_ttf.h"
#include "SharedContext.h"

class UserInterface : public IManager
{
public:
	explicit UserInterface(SDL_Window& p_window, SDL_Renderer& p_renderer, SharedContext& p_sharedContext);
	~UserInterface();

	void Setup() override;
	void Update() override;
	void Draw();
	void Close() override;

private:
	TTF_Font* m_font;
	SDL_Window& m_window;
	SDL_Renderer& m_renderer;
	SharedContext& m_sharedContext;
};
