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
	m_font = TTF_OpenFont("../assets/arial.ttf", 50);
}

void UserInterface::Update()
{
	Draw();
}

void UserInterface::Draw()
{
	std::string fps = std::to_string(m_sharedContext.fpsCounter);
	SDL_Surface* fpsCounter = TTF_RenderText_Blended(m_font, fps.c_str() , { 0, 255, 0 });
	SDL_Rect fpsCounterLocation = { 100, 100, 0, 0 };
	SDL_Texture* texture = SDL_CreateTextureFromSurface(&m_renderer, fpsCounter);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_RenderCopy(&m_renderer, texture, NULL, &dstrect);

	SDL_FreeSurface(fpsCounter);
	SDL_DestroyTexture(texture);
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
}
