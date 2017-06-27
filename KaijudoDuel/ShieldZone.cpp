#include "ShieldZone.h"


ShieldZone::ShieldZone() : mSlotsUsed(0)
{
}

ShieldZone::~ShieldZone()
{
}

//void ShieldZone::renderCards(int myPlayer)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->render(myPlayer);
//	}
//}
//
//void ShieldZone::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void ShieldZone::addCard(Card* c)
{
	int cn = 0;
	int i = 1;
	for (i = 1;; i *= 2)
	{
		if (!(mSlotsUsed&i))
			break;
		cn++;
		if (cn > 32)
		{
			//cout << "ERROR: Shield zone add card ERROR" << endl;
			return;
		}
	}
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cn * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*cards.size() + CONST_CARDSEPERATION/2, mPos.y, mPos.z + (mPos.z + mHeight) / 2));
	c->flip();
	c->untap();
	mCards.push_back(c);
	mSlotsUsed |= i;
}

void ShieldZone::removeCard(Card* c)
{
	for (std::vector<Card*>::iterator i = mCards.begin(); i != mCards.end(); i++)
	{
		if (*i == c)
		{
			mCards.erase(i);
			break;
		}
	}
}

