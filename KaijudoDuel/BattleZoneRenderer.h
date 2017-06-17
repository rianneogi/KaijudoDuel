#pragma once

#include "ShieldZoneRenderer.h"

class BattleZoneRenderer : public ZoneRenderer
{
public:
	BattleZoneRenderer();
	~BattleZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped);
};

