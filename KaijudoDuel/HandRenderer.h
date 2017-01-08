#pragma once

#include "ZoneRenderer.h"

class HandRenderer : public ZoneRenderer
{
public:
	Camera* mCamera;

	HandRenderer();
	~HandRenderer();

	void addCard(CardModel* c);
	//void removeCard(CardModel* c);

	void update(int hovercard);
	void setCamera(Camera* cam);
};

