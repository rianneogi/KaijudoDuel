#pragma once

#include "Zone.h"

const float gHandStraightDistance = 10.f;
const float gHandDownDistance = 5.f;
const float gHandHoverStraightDistance = 4.f;
const float gHandHoverDownDistance = 2.f;

class Hand : public Zone
{
public:
	int mMyPlayer;
	Camera* mCamera;

	Hand();
	Hand(int p);
	~Hand();

	//void renderCards(int myPlayer);
	//void setCamera(Camera* cam);
	//void update(int hovercard);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
	void flipAllCards();
};

