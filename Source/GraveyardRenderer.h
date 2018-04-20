#pragma once

#include "DeckRenderer.h"

class GraveyardRenderer : public ZoneRenderer
{
public:
	int mIsOpen;
	int mScrollPos;

	GraveyardRenderer();
	~GraveyardRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
};

