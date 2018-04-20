#pragma once

#include "ManaZoneRenderer.h"

class ShieldZoneRenderer : public ZoneRenderer
{
public:
	ShieldZoneRenderer();
	~ShieldZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
	//void removeCard(CardModel* c);
};

