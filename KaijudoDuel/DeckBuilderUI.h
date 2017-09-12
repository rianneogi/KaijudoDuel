#pragma once

#include "DuelInterface.h"

class DeckBuilderUI
{
public:
	DeckBuilderUI();
	~DeckBuilderUI();

	void update(int deltaTime);
	void render();
	int handleEvent(const SDL_Event& event, int callback);
};

