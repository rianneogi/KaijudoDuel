#pragma once

#include "HandRenderer.h"

class DeckRenderer : public ZoneRenderer
{
public:
	DeckRenderer();
	~DeckRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped);
};

