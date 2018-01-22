#include "EventManager.h"

EventManager::EventManager(SharedContext& p_sharedContext)
	: m_sharedContext(p_sharedContext)
{
	EventManager::Setup();
}

EventManager::~EventManager() { EventManager::Update(); }

void EventManager::Setup()
{
}

void EventManager::Update()
{
	while (SDL_PollEvent(&m_event))
	{
		switch (m_event.type)
		{
		case SDL_QUIT:
			m_sharedContext.appInfos.isRunning = false;
			break;
		case SDL_KEYDOWN:
			KeyInput(m_event.key.keysym, true);
			break;
		case SDL_KEYUP:
			KeyInput(m_event.key.keysym, false);
			break;
		default:
			break;
		}
	}
}

void EventManager::KeyInput(const SDL_Keysym& p_key, const bool p_state) const
{
	if (m_sharedContext.appInfos.selectedVersion == 8)
		return;

	if (!p_state)
	{
		m_sharedContext.appInfos.keyHistory.AddKey(p_key.sym);
		if (m_sharedContext.appInfos.keyHistory.IsKonamiCode())
		{
			m_sharedContext.soundEngine->play2D("../assets/sounds/zelda.wav");
			m_sharedContext.appInfos.selectedVersion = 8;
			m_sharedContext.appInfos.zelda.Reset();
			m_sharedContext.appInfos.keyHistory.Reset();
			m_sharedContext.actions.Reset();
			m_sharedContext.RefreshScene();
		}
	}

	switch (p_key.sym)
	{
	case SDLK_w:
		m_sharedContext.actions.zoomIn = p_state;
		break;
	case SDLK_s:
		m_sharedContext.actions.zoomOut = p_state;
		break;
	case SDLK_a:
		m_sharedContext.actions.moveLeft = p_state;
		break;
	case SDLK_d:
		m_sharedContext.actions.moveRight = p_state;
		break;
	case SDLK_q:
		m_sharedContext.actions.moveDown = p_state;
		break;
	case SDLK_e:
		m_sharedContext.actions.moveUp = p_state;
		break;
	case SDLK_LEFT:
		if (m_sharedContext.appInfos.selectedVersion == 7)
			m_sharedContext.actions.zTurnClockwise = p_state;
		else
			m_sharedContext.actions.yTurnClockwise = p_state;
		break;
	case SDLK_RIGHT:
		if (m_sharedContext.appInfos.selectedVersion == 7)
			m_sharedContext.actions.zTurnCounterClockwise = p_state;
		else
			m_sharedContext.actions.yTurnCounterClockwise = p_state;
		break;
	case SDLK_UP:
		m_sharedContext.actions.xTurnClockwise = p_state;
		break;
	case SDLK_DOWN:
		m_sharedContext.actions.xTurnCounterClockwise = p_state;
		break;
	case SDLK_KP_1:
	case SDLK_1:
		m_sharedContext.appInfos.selectedVersion = 1;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_2:
	case SDLK_2:
		m_sharedContext.appInfos.selectedVersion = 2;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_3:
	case SDLK_3:
		m_sharedContext.appInfos.selectedVersion = 3;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_4:
	case SDLK_4:
		m_sharedContext.appInfos.selectedVersion = 4;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_5:
	case SDLK_5:
		m_sharedContext.appInfos.selectedVersion = 5;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_6:
	case SDLK_6:
		m_sharedContext.appInfos.selectedVersion = 6;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_7:
	case SDLK_7:
		m_sharedContext.appInfos.selectedVersion = 7;
		m_sharedContext.RefreshScene();
		break;
	case SDLK_KP_8:
	case SDLK_8:
		m_sharedContext.appInfos.selectedLight = AMBIANT;
		break;
	case SDLK_KP_9:
	case SDLK_9:
		m_sharedContext.appInfos.selectedLight = DIFFUSE;
		break;
	case SDLK_KP_0:
	case SDLK_0:
		m_sharedContext.appInfos.selectedLight = SPECULAR;
		break;
	case SDLK_KP_PLUS:
	case SDLK_PAGEUP:
		m_sharedContext.actions.increaseLight = p_state;
		break;
	case SDLK_KP_MINUS:
	case SDLK_PAGEDOWN:
		m_sharedContext.actions.decreaseLight = p_state;
		break;
	case SDLK_r:
		m_sharedContext.actions.addRed = p_state;
		break;
	case SDLK_g:
		m_sharedContext.actions.addGreen = p_state;
		break;
	case SDLK_b:
		m_sharedContext.actions.addBlue = p_state;
		break;
	case SDLK_t:
		m_sharedContext.actions.addTransparency = p_state;
		break;
	case SDLK_h:
		m_sharedContext.actions.showHelp = p_state;
		break;
	case SDLK_m:
		m_sharedContext.actions.changeAAValue = p_state;
		if (p_state)
		{
			if (m_sharedContext.appInfos.selectedVersion == 7)
			{
				++m_sharedContext.appInfos.selectedAA;
				if (m_sharedContext.appInfos.selectedAA > 4)
					m_sharedContext.appInfos.selectedAA = 0;
			}
			else if (m_sharedContext.appInfos.selectedVersion >= 1 && m_sharedContext.appInfos.selectedVersion <= 3)
			{
				if (m_sharedContext.appInfos.selectedAA == 3)
					m_sharedContext.appInfos.selectedAA = 0;
				else
					m_sharedContext.appInfos.selectedAA = 3;
			}
		}
		break;
	case SDLK_ESCAPE:
		m_sharedContext.appInfos.Reset();
		break;
	case SDLK_F1:
		if (p_state)
			m_sharedContext.appInfos.showInterface = !m_sharedContext.appInfos.showInterface;
		break;
	case SDLK_F2:
		if (p_state)
		{
			if (m_sharedContext.appInfos.meshMode == CUBE)
				m_sharedContext.appInfos.meshMode = SPHERE;
			else if (m_sharedContext.appInfos.meshMode == SPHERE)
				m_sharedContext.appInfos.meshMode = CUBE;

			m_sharedContext.RefreshScene();
		}
		break;
	case SDLK_F3:
		if (p_state && (m_sharedContext.appInfos.selectedVersion == 5 || m_sharedContext.appInfos.selectedVersion == 6))
		{
			uint8_t& imageID = m_sharedContext.appInfos.meshMode == CUBE ? m_sharedContext.appInfos.meshParams.cubeImageID : m_sharedContext.appInfos.meshParams.sphereImageID;
			std::vector<Image*>& textureContainer = m_sharedContext.appInfos.meshMode == CUBE ? m_sharedContext.scene->cubeTextures : m_sharedContext.scene->sphereTextures;
			++imageID;
			if (imageID > textureContainer.size() - 1)
				imageID = 0;
		}
		break;
	default:
		break;
	}
}


void EventManager::Close()
{
}
