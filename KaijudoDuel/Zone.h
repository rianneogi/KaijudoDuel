#pragma once

#include "Card.h"
#include "CRandom.h"

const float CONST_CARDSEPERATION = 2.2f;
const float CONST_CARDELEVATION = 0.1f;
const float CONST_CARDTHICKNESS = 0.0125f;

class Zone
{
public:
	int owner;
	std::vector<Card*> cards;
	
	glm::vec3 mPos;
	float mWidth;
	float mHeight;

	Zone();
	Zone(glm::vec3 p, float w, float h);
	~Zone();

	//void render(sf::RenderWindow& window);
	virtual void renderCards(int myPlayer) = 0;
	virtual void addCard(Card* c) = 0;
	//virtual void handleEvent(sf::Event event) = 0;
	//sf::FloatRect getBounds();
	virtual void removeCard(Card* id);
};

