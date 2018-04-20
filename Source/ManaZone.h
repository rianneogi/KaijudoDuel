#pragma once

#include "Graveyard.h"

class ManaZone : public Zone
{
public:
	ManaZone();
	~ManaZone();

	//void renderCards(int myPlayer);
	//void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
	int getUntappedMana();
	void tapMana(int count);
};

