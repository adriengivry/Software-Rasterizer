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
	case SDLK_LEFT:
		m_sharedContext.actions.yTurnClockwise = p_state;
		break;
	case SDLK_RIGHT:
		m_sharedContext.actions.yTurnCounterClockwise = p_state;
		break;
	case SDLK_UP:
		m_sharedContext.actions.xTurnClockwise = p_state;
		break;
	case SDLK_DOWN:
		m_sharedContext.actions.xTurnCounterClockwise = p_state;
		break;
	case SDLK_8:
		m_sharedContext.appInfos.selectedLight = AMBIANT;
		break;
	case SDLK_9:
		m_sharedContext.appInfos.selectedLight = DIFFUSE;
		break;
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
	default:
		break;
	}

	if (p_key.sym >= 49 && p_key.sym <= 55)
		m_sharedContext.appInfos.selectedVersion = p_key.sym - 48;
}


void EventManager::Close()
{
}
