#pragma once

#include "GraveyardRenderer.h"

class ManaZoneRenderer : public ZoneRenderer
{
public:
	ManaZoneRenderer();
	~ManaZoneRenderer();

	void addCard(CardModel* c);
	//void removeCard(CardModel* c);
};

