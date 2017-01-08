#pragma once

#include "Hand.h"

class Deck : public Zone
{
public:
	Deck();
	~Deck();

	CRandom* RandomGen;

	Card* draw();
	int getTopCard();

	//void renderCards(int myPlayer);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void shuffle();
	//void loadFromFile(string s, int uid);
};

