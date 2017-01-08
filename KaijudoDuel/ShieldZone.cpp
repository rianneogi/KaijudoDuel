#include "ShieldZone.h"


ShieldZone::ShieldZone() : slotsUsed(0)
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
		if (!(slotsUsed&i))
			break;
		cn++;
		if (cn > 32)
		{
			//cout << "ERROR: Shield zone add card ERROR" << endl;
			return;
		}
	}
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cn * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*cards.size() + CONST_CARDSEPERATION/2, mPos.y, mPos.z + (mPos.z + mHeight) / 2));
	c->flip();
	c->untap();
	cards.push_back(c);
	slotsUsed |= i;
}

void ShieldZone::removeCard(Card* c)
{
	for (std::vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if (*i == c)
		{
			cards.erase(i);
			break;
		}
	}
}

