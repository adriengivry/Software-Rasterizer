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
	const std::string fps = std::to_string(m_sharedContext.appInfos.fpsCounter) + " FPS (" + std::to_string(m_sharedContext.appInfos.minFps) + " to " + std::to_string(m_sharedContext.appInfos.maxFps) + " FPS | ~" + std::to_string(m_sharedContext.appInfos.averageFps) + " FPS)";
	DrawAt(fps, 0, 0);


	std::string items[] = { "1. Z-Buffer", "2. Phong (Per-Vertex)", "3. Blinn-Phong (Per-Pixel)", "4. Wireframe", "5. Texture", "6. Alpha-Blending", "7. Antialiasing" };
	for (uint8_t i = 0; i < 7; ++i)
		DrawAt(items[i], 0, 200 + i * 23);
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
}

void UserInterface::DrawAt(std::string p_text, uint16_t p_x, uint16_t p_y) const
{
	SDL_Surface* itemSurface = TTF_RenderText_Blended(m_font, p_text.c_str(), { 255, 255, 255, 255 });
	SDL_Texture* itemTexture = SDL_CreateTextureFromSurface(m_sharedContext.window->GetRenderer(), itemSurface);
	int itemTextureWidth = 0;
	int itemTextureHeight = 0;
	SDL_QueryTexture(itemTexture, nullptr, nullptr, &itemTextureWidth, &itemTextureHeight);
	SDL_Rect dstrect = { p_x, p_y, itemTextureWidth, itemTextureHeight };
	SDL_RenderCopy(m_sharedContext.window->GetRenderer(), itemTexture, nullptr, &dstrect);
	SDL_FreeSurface(itemSurface);
	SDL_DestroyTexture(itemTexture);
}
