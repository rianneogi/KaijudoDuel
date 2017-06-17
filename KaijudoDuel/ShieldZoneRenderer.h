#pragma once

#include "ManaZoneRenderer.h"

class ShieldZoneRenderer : public ZoneRenderer
{
public:
	ShieldZoneRenderer();
	~ShieldZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped);
	//void removeCard(CardModel* c);
};

