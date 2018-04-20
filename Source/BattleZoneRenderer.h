#pragma once

#include "ShieldZoneRenderer.h"

class BattleZoneRenderer : public ZoneRenderer
{
public:
	BattleZoneRenderer();
	~BattleZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
};

