#pragma once

#include "ShieldZoneRenderer.h"

class BattleZoneRenderer : public ZoneRenderer
{
public:
	BattleZoneRenderer();
	~BattleZoneRenderer();

	void addCard(CardModel* c);
};

