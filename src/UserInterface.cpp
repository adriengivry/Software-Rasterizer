#include "UserInterface.h"
#include <string>

UserInterface::UserInterface(SDL_Window& p_window, SDL_Renderer& p_renderer, SharedContext& p_sharedContext)
	: m_font(nullptr),
	m_window(p_window),
	m_renderer(p_renderer),
	m_sharedContext(p_sharedContext)
{
	UserInterface::Setup();
}

UserInterface::~UserInterface()
{
	UserInterface::Close();
}

void UserInterface::Setup()
{
	m_font = TTF_OpenFont("../assets/arial.ttf", 20);
}

void UserInterface::Update()
{
	Draw();
}

void UserInterface::Draw()
{
	// CURRENT FPS
	std::string fps = std::to_string(m_sharedContext.fpsCounter) + " FPS";
	if (SDL_GetTicks() / 1000 > 5.f)
	{
		fps += " (" + std::to_string(m_sharedContext.minFps) + " to " + std::to_string(m_sharedContext.maxFps) + " FPS | ~" + std::to_string(m_sharedContext.averageFps) + " FPS)";
	}

	SDL_Surface* fpsCounter = TTF_RenderText_Blended(m_font, fps.c_str() , { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(&m_renderer, fpsCounter);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_RenderCopy(&m_renderer, texture, nullptr, &dstrect);

	SDL_FreeSurface(fpsCounter);
	SDL_DestroyTexture(texture);
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
}
