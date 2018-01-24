#include "UserInterface.h"
#include <string>


UserInterface::UserInterface(SharedContext& p_sharedContext)
	: m_font(nullptr), 
	m_smallFont(nullptr),
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
	m_font = TTF_OpenFont("../assets/fonts/arial.ttf", 16);
	m_smallFont = TTF_OpenFont("../assets/fonts/arial.ttf", 12);
	m_pixelFont = TTF_OpenFont("../assets/fonts/pixelart.ttf", 30);

	m_labelsVersions[0] = "RASTERIZER FEATURES";
	m_labelsVersions[1] = "[1] Z-Buffer";
	m_labelsVersions[2] = "[2] Phong (Per-Vertex)";
	m_labelsVersions[3] = "[3] Blinn-Phong (Per-Pixel)";
	m_labelsVersions[4] = "[4] Wireframe with Backface Culling";
	m_labelsVersions[5] = "[5] Bilinear filtering";
	m_labelsVersions[6] = "[6] Alpha-Blending";
	m_labelsVersions[7] = "[7] Anti-aliasing";
}

void UserInterface::Update()
{
}

void UserInterface::Draw()
{
	if (m_sharedContext.appInfos.selectedVersion != 0)
	{
		DrawFPS();
		DrawHelp();

		if (m_sharedContext.appInfos.showInterface)
		{
			DrawCameraParams();
			DrawSceneInfo();
			DrawVersionSelection();
			DrawMeshProperties();
			DrawLightProperties();
			DrawAntiAliasingProperties();
			DrawCredits();
		}
	}
	else
	{
		DrawZelda();
	}
}

void UserInterface::DrawFPS()
{
	
	std::string fpsInfo[] =
	{
		"FPS counter",
		"Current: " + std::to_string(m_sharedContext.appInfos.fpsCounter),
		"Min.: " + std::to_string(m_sharedContext.appInfos.minFps),
		"Max.: " + std::to_string(m_sharedContext.appInfos.maxFps),
		"Average: " + std::to_string(m_sharedContext.appInfos.averageFps),

	};
	
	for (uint8_t i = 0; i < 5; ++i)
	{
		if (i == 0)
			SetTextTitleColor();
		else
			SetTextSelectedColor();
		DrawAt(fpsInfo[i], 0, i * 15, m_smallFont);
	}
}

void UserInterface::DrawCameraParams()
{
	std::string cameraParams[] =
	{
		"Camera Parameters",
		"X-Pos: " + std::to_string(m_sharedContext.appInfos.cameraParams.xOffset),
		"Y-Pos: " + std::to_string(m_sharedContext.appInfos.cameraParams.yOffset),
		"Z-Pos: " + std::to_string(m_sharedContext.appInfos.cameraParams.zoomOffset),
		"X-Rotation: " + std::to_string(m_sharedContext.appInfos.cameraParams.xRotationOffset),
		"Y-Rotation: " + std::to_string(m_sharedContext.appInfos.cameraParams.yRotationOffset)
	};

	uint8_t thingsToShow = 6;

	if (m_sharedContext.appInfos.selectedVersion == 7)
	{
		thingsToShow = 4;
	}

	for (uint8_t i = 0; i < thingsToShow; ++i)
	{
		if (i == 0)
			SetTextTitleColor();
		else
			SetTextSelectedColor();
		DrawAt(cameraParams[i], 350, i * 15, m_smallFont);
	}
}

void UserInterface::DrawSceneInfo()
{
	std::string sceneInfo[] =
	{
		"Scene Info",
		"Polygons: " + std::to_string(m_sharedContext.appInfos.polygons),
		"Entities: " + std::to_string(m_sharedContext.scene->entities.size()),
		"Meshes: " + std::to_string(m_sharedContext.scene->meshes.size()),
		"Lights: " + std::to_string(m_sharedContext.scene->lights.size())
	};

	for (uint8_t i = 0; i < 5; ++i)
	{
		if (i == 0)
			SetTextTitleColor();
		else
			SetTextSelectedColor();
		DrawAt(sceneInfo[i], 600, i * 15, m_smallFont);
	}
}

void UserInterface::DrawVersionSelection()
{
	for (uint8_t i = 0; i < 8; ++i)
	{
		SetTextDefaultColor();
		if (i == m_sharedContext.appInfos.selectedVersion) SetTextSelectedColor();
		if (i == 0) SetTextTitleColor();
		DrawAt(m_labelsVersions[i], 0, 147 + i * 20);
	}
}

void UserInterface::DrawMeshProperties()
{
	if (m_sharedContext.appInfos.selectedVersion < 5 || m_sharedContext.appInfos.selectedVersion == 7)
	{
		std::string items[] =
		{
			"MESH PROPERTIES",
			"[R]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.meshParams.red)),
			"[G]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.meshParams.green)),
			"[B]: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.meshParams.blue))
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
			DrawAt(items[i], 0, 350 + i * 20);
		}
	}

	if (m_sharedContext.appInfos.selectedVersion == 6)
	{
		std::string items[] =
		{
			"MESH PROPERTIES",
			"[T]ransparency: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.meshParams.transparency)) + "%"
		};

		for (uint8_t i = 0; i < 2; ++i)
		{
			SetTextDefaultColor();
			if (m_sharedContext.actions.addTransparency) SetTextSelectedColor();
			if (i == 0) SetTextTitleColor();
			DrawAt(items[i], 0, 350 + i * 20);
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
			"[Z] Ambiant: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.ambiant)),
			"[X] Diffuse: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.diffuse)),
			"[C] Specular: " + std::to_string(static_cast<uint8_t>(m_sharedContext.appInfos.lightParams.specular))
		};

		for (uint8_t i = 0; i < 4; ++i)
		{
			SetTextDefaultColor();
			bool lightIsChanging = false;

			switch (i)
			{
			default: break;
			case 1: lightIsChanging = m_sharedContext.actions.addAmbiant;	break;
			case 2: lightIsChanging = m_sharedContext.actions.addDiffuse;	break;
			case 3: lightIsChanging = m_sharedContext.actions.addSpecular;	break;
			}

			if (lightIsChanging) SetTextSelectedColor();
			if (i == 0) SetTextTitleColor();
			DrawAt(items[i], 0, 535 + i * 20);
		}
	}
}

void UserInterface::DrawAntiAliasingProperties()
{
	if (m_sharedContext.appInfos.selectedVersion == 7 || (m_sharedContext.appInfos.selectedVersion >= 1 && m_sharedContext.appInfos.selectedVersion <= 3))
	{
		std::string currentMode;
		switch (m_sharedContext.appInfos.selectedAA)
		{
		case NOAA:
			currentMode = "Off";
			break;
		case AA2X:
			currentMode = "MSAA 2x";
			break;
		case AA4X:
			currentMode = "MSAA 4x";
			break;
		case AA8X:
			currentMode = "MSAA 8x";
			break;
		case AA16X:
			currentMode = "MSAA 16x";
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
			DrawAt(items[i], 0, 465 + i * 20);
		}
	}
}

void UserInterface::DrawHelp()
{
	if (m_sharedContext.actions.showHelp)
	{
		uint16_t yBuffer = 250;
		uint16_t xPos = 850;
		std::string general[] =
		{
			"Shortcuts",
			"Hold [H] for help",
			"[ESC] to reset settings",
			"[F1] to hide/show interface",
			"[F2] to switch Cube/Sphere",
			"[F3] to change mesh texture",
			"",
			"Feature Selection",
			"Use [1-7] numbers to select",
			"a feature to render on screen."
		};

		for (uint8_t i = 0; i < 9; ++i)
		{
			SetTextDefaultColor();
			SetTextSelectedColor();
			if (i == 0 || i == 7)
			{
				SetTextTitleColor();
				DrawAt(general[i], 850, yBuffer);
				yBuffer += 20;
			}
			else
			{
				DrawAt(general[i], xPos, yBuffer, m_smallFont);
				yBuffer += 15;
			}
		}

		if (m_sharedContext.appInfos.selectedVersion != 5)
		{
			yBuffer += 15;
			std::string bracketHelp[] =
			{
				"Changing values",
				"Press the key relative to the",
				"letter in brackets [X] to modify",
				"the value attached to the item."
			};

			for (uint8_t i = 0; i < 4; ++i)
			{
				SetTextDefaultColor();
				SetTextSelectedColor();
				if (i == 0)
				{
					SetTextTitleColor();
					DrawAt(bracketHelp[i], 850, yBuffer);
					yBuffer += 20;
				}
				else
				{
					DrawAt(bracketHelp[i], xPos, yBuffer, m_smallFont);
					yBuffer += 15;
				}
			}
		}
	}
	else
	{
		SetTextSelectedColor();
		DrawAt("Press [H] for help!", 925, 0, m_smallFont);
	}
}

void UserInterface::DrawCredits()
{
	SetTextSelectedColor();
	DrawAt("CPU Rasterizer student project by Hanseul SHIN & Adrien GIVRY", 350, 754, m_smallFont);
}

void UserInterface::DrawKonamiCode()
{
	std::string currentCode;
	for (SDL_Keycode key : m_sharedContext.appInfos.keyHistory.keys)
		currentCode.push_back(key);

	SetTextSelectedColor();
	DrawAt(currentCode, 500, 700, m_smallFont);
}

void UserInterface::DrawZelda()
{
	DrawAt("© 2017-2018 Hansdrien Inc.", 380, 700, m_pixelFont);
}

void UserInterface::Close()
{
	TTF_CloseFont(m_font);
	TTF_CloseFont(m_smallFont);
	TTF_CloseFont(m_pixelFont);
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

void UserInterface::DrawAt(const std::string& p_text, uint16_t p_x, uint16_t p_y, TTF_Font* p_font) const
{
	TTF_Font* fontToUse = m_font;

	if (p_font)
		fontToUse = p_font;

	SDL_Surface* itemSurface = TTF_RenderText_Blended(fontToUse, p_text.c_str(), { static_cast<uint8_t>(m_textColor.r), static_cast<uint8_t>(m_textColor.g), static_cast<uint8_t>(m_textColor.b), 255 });
	SDL_Texture* itemTexture = SDL_CreateTextureFromSurface(m_sharedContext.window->GetRenderer(), itemSurface);
	int itemTextureWidth = 0;
	int itemTextureHeight = 0;
	SDL_QueryTexture(itemTexture, nullptr, nullptr, &itemTextureWidth, &itemTextureHeight);
	SDL_Rect dstrect = { p_x, p_y, itemTextureWidth, itemTextureHeight };
	SDL_RenderCopy(m_sharedContext.window->GetRenderer(), itemTexture, nullptr, &dstrect);
	SDL_FreeSurface(itemSurface);
	SDL_DestroyTexture(itemTexture);
}
