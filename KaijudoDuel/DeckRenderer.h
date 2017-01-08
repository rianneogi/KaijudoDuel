#pragma once

#include "HandRenderer.h"

class DeckRenderer : public ZoneRenderer
{
public:
	DeckRenderer();
	~DeckRenderer();

	void addCard(CardModel* c);
};

