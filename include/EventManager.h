#pragma once
#include "IManager.h"
#include <SDL.h>
#include "SharedContext.h"

class EventManager : public IManager
{
public:
	explicit EventManager(SharedContext& p_sharedContext);
	~EventManager();

	void Setup() override;
	void Update() override;
	void Close() override;

private:
	SDL_Event m_event;
	SharedContext& m_sharedContext;
};
