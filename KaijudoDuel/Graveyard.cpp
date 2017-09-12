#include "Graveyard.h"

Graveyard::Graveyard()
{
}

Graveyard::~Graveyard()
{
}

//void Graveyard::renderCards(int myPlayer)
//{
//	if (cards.size() != 0)
//	{
//		cards.at(cards.size() - 1)->render(myPlayer);
//	}
//}

//
//void Graveyard::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void Graveyard::addCard(Card* c)
{
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*cards.size(), mPos.z + (mPos.z + mHeight) / 2));
	c->unflip();
	c->untap();
	c->mIsVisible[0] = true;
	c->mIsVisible[1] = true;
	mCards.push_back(c);
}