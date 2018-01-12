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
			m_sharedContext.isRunning = false;
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
	default:
		break;
	}
}


void EventManager::Close()
{
}
