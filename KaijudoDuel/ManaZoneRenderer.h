#pragma once

#include "GraveyardRenderer.h"

class ManaZoneRenderer : public ZoneRenderer
{
public:
	ManaZoneRenderer();
	~ManaZoneRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size);
	//void removeCard(CardModel* c);
};

