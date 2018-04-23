#include "BattleZone.h"

BattleZone::BattleZone()
{
}

BattleZone::~BattleZone()
{
}

//void BattleZone::renderCards(int myPlayer)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->render(myPlayer);
//	}
//}

//void BattleZone::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void BattleZone::addCard(Card* c)
{
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*cards.size(), mPos.y, mPos.z + (mPos.z+mHeight)/2));
	c->unflip();
	c->untap();
	c->mSummoningSickness = 1;
	c->mIsVisible[0] = true;
	c->mIsVisible[1] = true;
	mCards.push_back(c);
}

//void BattleZone::addCard(Card* c, int speedattacker)
//{
//	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
//	c->unflip();
//	c->untap();
//	c->summoningSickness = (speedattacker+1)%2;
//	cards.push_back(c);
//}

void BattleZone::evolveCard(Card* c, int evobait)
{
	Card* eb = NULL;
	int ebloc = 0;
	for (std::vector<Card*>::iterator i = mCards.begin(); i != mCards.end(); i++)
	{
		if ((*i)->mUniqueId == evobait)
		{
			eb = *i;
			break;
		}
		ebloc++;
	}
	if (eb == NULL)
	{
		printf("ERROR: attempting to evolve on card not in battlezone, cid: %d\n", evobait);
		return;
	}
	//sf::FloatRect r = eb->sprite.getGlobalBounds();
	//c->move(r.left + r.width/2, r.top + r.height/2);
	c->unflip();
	c->untap();
	c->mIsVisible[0] = true;
	c->mIsVisible[1] = true;
	c->mSummoningSickness = 0;
	eb->mZone = ZONE_EVOLVED;
	c->mEvoStack.push_back(eb);
	mCards.at(ebloc) = c;
}

void BattleZone::removeCard(Card* c)
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

void BattleZone::seperateEvolution(Card* c)
{
	//vector<Card*>::iterator eb = cards.begin();
	int flag = 0;
	int eb = -1;

	for (eb = 0; eb < mCards.size(); eb++)
	{
		if (mCards.at(eb) == c)
		{
			flag = 1;
			eb;
			break;
		}
	}

	if (flag==0)
	{
		//cout << "ERROR: attempting to seperate evolution stack not in battlezone, evo name: " << c->Name << endl;
		return;
	}

	for (std::vector<Card*>::iterator i = c->mEvoStack.begin(); i != c->mEvoStack.end(); i++)
	{
		(*i)->mZone = ZONE_BATTLE;
		mCards.insert(mCards.begin()+eb, *i);
	}
	c->mEvoStack.clear();
}

//void BattleZone::removeBait(Card* c)
//{
//	int x = 0;
//	for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
//	{
//		if (*i == c)
//		{
//			cards.erase(i);
//			break;
//		}
//		x++;
//	}
//}

