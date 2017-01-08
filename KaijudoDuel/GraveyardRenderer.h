#pragma once

#include "DeckRenderer.h"

class GraveyardRenderer : public ZoneRenderer
{
public:
	GraveyardRenderer();
	~GraveyardRenderer();

	void addCard(CardModel* c);
};

