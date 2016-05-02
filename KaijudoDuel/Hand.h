#pragma once

#include "Zone.h"

class Hand : public Zone
{
public:
	int myPlayer;

	Hand();
	Hand(int p);
	~Hand();

	void renderCards(int myPlayer);
	void update(const Camera& camera, int hovercard);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
	void flipAllCards();
};

