#pragma once

#include "ZoneRenderer.h"

class HandRenderer : public ZoneRenderer
{
public:
	Camera* mCamera;
	int mHoverCard;

	HandRenderer();
	~HandRenderer();

	void addCard(CardModel* c);
	void updateCard(CardModel* c, int pos, int size);
	//void removeCard(CardModel* c);

	void update(int hovercard);
	void setCamera(Camera* cam);
};

