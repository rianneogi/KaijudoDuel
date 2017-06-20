#pragma once

#include "ZoneRenderer.h"

const float gHandStraightDistance = 10.f;
const float gHandDownDistance = 6.5f;
const float gHandHoverStraightDistance = 4.f;
const float gHandHoverDownDistance = 2.f;
const float gHandRightDistance = 3.f;
const float gHandHoverRightDistance = 1.5f;
const float gHighlightX = 0;
const float gHighlightY = 20;
const float gHighlightZ = 0;

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

