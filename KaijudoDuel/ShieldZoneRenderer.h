#pragma once

#include "ManaZoneRenderer.h"

class ShieldZoneRenderer : public ZoneRenderer
{
public:
	ShieldZoneRenderer();
	~ShieldZoneRenderer();

	void addCard(CardModel* c);
	//void removeCard(CardModel* c);
};

