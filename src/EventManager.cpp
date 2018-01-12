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
		}
	}
}

void EventManager::Close()
{
}
