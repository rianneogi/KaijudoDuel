#pragma once

#include "ZoneRenderer.h"

class HandRenderer : public ZoneRenderer
{
public:
	Camera* mCamera;
	int mOwner;
	int mTurn;

	HandRenderer(int owner);
	~HandRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped);
	//void removeCard(CardModel* c);

	void update(int hovercard);
	void setCamera(Camera* cam);
};

