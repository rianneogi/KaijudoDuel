#pragma once

#include "ZoneRenderer.h"

class HandRenderer : public ZoneRenderer
{
public:
	Camera* mCamera;
	int mOwner;
	int mTurn;
	int mCastingCard;

	HandRenderer(int owner);
	~HandRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* model, Card* card, int pos, int size, int hovercard);
	//void removeCard(CardModel* c);

	void update(int hovercard);
	void setCamera(Camera* cam);
};
