#pragma once
#include "IManager.h"
#include "SDL_ttf.h"
#include "SharedContext.h"

class UserInterface : public IManager
{
public:
	explicit UserInterface(SharedContext& p_sharedContext);
	~UserInterface();

	void Setup() override;
	void Update() override;
	void Draw() const;
	void Close() override;

private:
	TTF_Font* m_font;
	SharedContext& m_sharedContext;
};
