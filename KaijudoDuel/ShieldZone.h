#pragma once

#include "ManaZone.h"

class ShieldZone : public Zone
{
public:
	ShieldZone();
	~ShieldZone();

	int slotsUsed;

	//void renderCards(int myPlayer);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
};

