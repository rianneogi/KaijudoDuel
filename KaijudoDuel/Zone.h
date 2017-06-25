#pragma once

#include "Card.h"
#include "CRandom.h"

const float CONST_CARDSEPERATION_VERT = 2.8f;
const float CONST_CARDSEPERATION_HORI = 2.f;
const float CONST_CARDELEVATION = 0.1f;
const float CONST_CARDTHICKNESS = 0.0125f;

class Zone
{
public:
	int owner;
	std::vector<Card*> cards;
	
	/*glm::vec3 mPos;
	float mWidth;
	float mHeight;*/

	Zone();
	//Zone(glm::vec3 p, float w, float h);
	~Zone();

	virtual void addCard(Card* c) = 0;
	virtual void removeCard(Card* c);
	
	//virtual void renderCards(int myPlayer) = 0;
	//bool rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions);
};

