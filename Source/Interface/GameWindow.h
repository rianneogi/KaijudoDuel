#include "BattleZoneRenderer.h"

class GameWindow
{
    virtual void update(int deltaTime) = 0;
	virtual void render() = 0;
	virtual int handleEvent(const SDL_Event& event, int callback) = 0;
};
