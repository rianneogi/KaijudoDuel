#pragma once

#include "Zone.h"

class Hand : public Zone
{
public:
	int mMyPlayer;
	//Camera* mCamera;

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

