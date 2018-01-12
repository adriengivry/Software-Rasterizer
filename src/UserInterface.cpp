#include "UserInterface.h"
#include <string>


UserInterface::UserInterface(SharedContext& p_sharedContext)
	: m_font(nullptr), 
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
}

void UserInterface::Draw() const
{
	// CURRENT FPS
	std::string fps = std::to_string(m_sharedContext.appInfos.fpsCounter) + " FPS";
	fps += " (" + std::to_string(m_sharedContext.appInfos.minFps) + " to " + std::to_string(m_sharedContext.appInfos.maxFps) + " FPS | ~" + std::to_string(m_sharedContext.appInfos.averageFps) + " FPS)";


	SDL_Surface* fpsCounter = TTF_RenderText_Blended(m_font, fps.c_str() , { 255, 255, 255, 255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_sharedContext.window->GetRenderer(), fpsCounter);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };
	SDL_RenderCopy(m_sharedContext.window->GetRenderer(), texture, nullptr, &dstrect);

	SDL_FreeSurface(fpsCounter);
	SDL_DestroyTexture(texture);
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
}
