#pragma once

#include "ManaZone.h"

class ShieldZone : public Zone
{
public:
	ShieldZone();
	~ShieldZone();

	int mSlotsUsed;

	//void renderCards(int myPlayer);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
};

