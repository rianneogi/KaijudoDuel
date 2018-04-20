#pragma once

#include "HandRenderer.h"

class DeckRenderer : public ZoneRenderer
{
public:
	int mIsOpen;
	int mScrollPos;

	DeckRenderer();
	~DeckRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
};

