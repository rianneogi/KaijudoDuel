#pragma once

#include "GraveyardRenderer.h"

class ManaZoneRenderer : public ZoneRenderer
{
public:
	ManaZoneRenderer();
	~ManaZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
	//void removeCard(CardModel* c);
};

