#pragma once

#include "DeckRenderer.h"

class GraveyardRenderer : public ZoneRenderer
{
public:
	GraveyardRenderer();
	~GraveyardRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped);
};

