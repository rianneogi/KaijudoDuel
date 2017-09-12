#include "ManaZone.h"

ManaZone::ManaZone()
{
}

ManaZone::~ManaZone()
{
}

//void ManaZone::renderCards(int myPlayer)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->render(myPlayer);
//	}
//}

//void ManaZone::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void ManaZone::addCard(Card* c)
{
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*cards.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
	c->unflip();
	c->untap();
	c->mIsVisible[0] = true;
	c->mIsVisible[1] = true;
	mCards.push_back(c);
}

void ManaZone::removeCard(Card* c)
{
	int x = 0;
	for (std::vector<Card*>::iterator i = mCards.begin(); i != mCards.end(); i++)
	{
		if (*i == c)
		{
			mCards.erase(i);
			break;
		}
		x++;
	}
	for (int i = x; i < mCards.size(); i++)
	{
		//cards.at(i)->setPosition(cards.at(i)->x - CARDSEPERATION, cards.at(i)->y);
	}
}

int ManaZone::getUntappedMana()
{
	int c = 0;
	for (std::vector<Card*>::iterator i = mCards.begin(); i != mCards.end(); i++)
	{
		if ((*i)->mIsTapped==false)
		{
			c++;
		}
	}
	return c;
}

void ManaZone::tapMana(int count)
{
	int c = 0;
	for (std::vector<Card*>::iterator i = mCards.begin(); i != mCards.end(); i++)
	{
		if ((*i)->mIsTapped == false)
		{
			(*i)->tap();
			c++;
			if (c >= count) break;
		}
	}
}

