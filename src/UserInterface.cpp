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

	m_labelsVersions[0] = "VERSION SELECTION";
	m_labelsVersions[1] = "1. Z-Buffer";
	m_labelsVersions[2] = "2. Phong (Per-Vertex)";
	m_labelsVersions[3] = "3. Blinn-Phong (Per-Pixel)";
	m_labelsVersions[4] = "4. Wireframe with Backface Culling";
	m_labelsVersions[5] = "5. Bilinear filtering";
	m_labelsVersions[6] = "6. Alpha-Blending";
	m_labelsVersions[7] = "7. Anti-aliasing";
}

void UserInterface::Update()
{
}

void UserInterface::Draw()
{
	DrawFPS();
	DrawVersionSelection();
	DrawMeshProperties();
	DrawLightProperties();	
	DrawAntiAliasingProperties();
}

void UserInterface::DrawFPS()
{
	SetTextSelectedColor();
	const std::string fps = std::to_string(m_sharedContext.appInfos.fpsCounter) + " FPS (" + std::to_string(m_sharedContext.appInfos.minFps) + " to " + std::to_string(m_sharedContext.appInfos.maxFps) + " FPS | ~" + std::to_string(m_sharedContext.appInfos.averageFps) + " FPS)";
	DrawAt(fps, 0, 0);
}

void UserInterface::DrawVersionSelection()
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		SetTextDefaultColor();
		if (i == m_sharedContext.appInfos.selectedVersion) SetTextSelectedColor();
		if (i == 0) SetTextTitleColor();
		DrawAt(m_labelsVersions[i], 0, 147 + i * 23);
	}
}

void UserInterface::DrawMeshProperties()
{
	if (m_sharedContext.appInfos.selectedVersion < 5)
	{
		std::string items[] =
		{
			"MESH PROPERTIES",
			"[R]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.cubeParams.red)),
			"[G]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.cubeParams.green)),
			"[B]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.cubeParams.blue))
		};

		for (uint8_t i = 0; i < 4; ++i)
		{
			SetTextDefaultColor();
			bool colorIsChanging = false;

			switch (i)
			{
				default: break;
				case 1: colorIsChanging = m_sharedContext.actions.addRed;	break;
				case 2: colorIsChanging = m_sharedContext.actions.addGreen; break;
				case 3: colorIsChanging = m_sharedContext.actions.addBlue;	break;
			}

			if (i == 0) SetTextTitleColor();
			if (colorIsChanging) SetTextSelectedColor();
			DrawAt(items[i], 0, 350 + i * 23);
		}
	}

	if (m_sharedContext.appInfos.selectedVersion == 6)
	{
		std::string items[] =
		{
			"MESH PROPERTIES",
			"[T]ransparency: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.cubeParams.transparency)) + "%"
		};

		for (uint8_t i = 0; i < 2; ++i)
		{
			SetTextDefaultColor();
			if (m_sharedContext.actions.addTransparency) SetTextSelectedColor();
			if (i == 0) SetTextTitleColor();
			DrawAt(items[i], 0, 350 + i * 23);
		}
	}
}

void UserInterface::DrawLightProperties()
{
	if (m_sharedContext.appInfos.selectedVersion == 2 || m_sharedContext.appInfos.selectedVersion == 3)
	{
		std::string items[] =
		{
			"LIGHT PROPERTIES",
			"8. Ambiant [" + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.ambiant)) + "]",
			"9. Diffuse [" + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.diffuse)) + "]",
			"0. Specular [" + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.specular)) + "]"
		};

		for (uint8_t i = 0; i < 4; ++i)
		{
			SetTextDefaultColor();
			if (i == m_sharedContext.appInfos.selectedLight) SetTextSelectedColor();
			if (i == 0) SetTextTitleColor();
			DrawAt(items[i], 0, 465 + i * 23);
		}
	}
}

void UserInterface::DrawAntiAliasingProperties()
{
	if (m_sharedContext.appInfos.selectedVersion == 7)
	{
		std::string currentMode;
		switch (m_sharedContext.appInfos.selectedAA)
		{
		case NOAA:
			currentMode = "Off";
			break;
		case AA2X:
			currentMode = "2x";
			break;
		case AA4X:
			currentMode = "4x";
			break;
		case AA8X:
			currentMode = "8x";
			break;
		case AA16X:
			currentMode = "16x";
			break;
		default:
			currentMode = "UNKNOWN";
			break;
		}
		std::string items[] =
		{
			"ANTI-ALIASING PROPERTIES",
			"[M]ode: " + currentMode
		};

		for (uint8_t i = 0; i < 2; ++i)
		{
			SetTextDefaultColor();
			if (m_sharedContext.actions.changeAAValue) SetTextSelectedColor();
			if (i == 0) SetTextTitleColor();
			DrawAt(items[i], 0, 350 + i * 23);
		}
	}
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
}

void UserInterface::SetTextSelectedColor()
{
	m_textColor.Set(255, 255, 255);
}

void UserInterface::SetTextDefaultColor()
{
	m_textColor.Set(125, 125, 125);
}

void UserInterface::SetTextTitleColor()
{
	m_textColor.Set(255, 255, 0);
}

void UserInterface::DrawAt(const std::string& p_text, uint16_t p_x, uint16_t p_y) const
{
	SDL_Surface* itemSurface = TTF_RenderText_Blended(m_font, p_text.c_str(), { static_cast<uint8_t>(m_textColor.r), static_cast<uint8_t>(m_textColor.g), static_cast<uint8_t>(m_textColor.b), 255 });
	SDL_Texture* itemTexture = SDL_CreateTextureFromSurface(m_sharedContext.window->GetRenderer(), itemSurface);
	int itemTextureWidth = 0;
	int itemTextureHeight = 0;
	SDL_QueryTexture(itemTexture, nullptr, nullptr, &itemTextureWidth, &itemTextureHeight);
	SDL_Rect dstrect = { p_x, p_y, itemTextureWidth, itemTextureHeight };
	SDL_RenderCopy(m_sharedContext.window->GetRenderer(), itemTexture, nullptr, &dstrect);
	SDL_FreeSurface(itemSurface);
	SDL_DestroyTexture(itemTexture);
}
