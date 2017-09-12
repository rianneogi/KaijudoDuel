#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
}

Card* Deck::draw()
{
	if (mCards.size() == 0) return NULL;
	Card* c = mCards.at(mCards.size()-1);
	mCards.pop_back();
	return c;
}

int Deck::getTopCard()
{
	return mCards.at(mCards.size() - 1)->mUniqueId;
}

//void Deck::renderCards(int myPlayer)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->render(myPlayer);
//	}
//}

//void Deck::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void Deck::addCard(Card* c)
{
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*cards.size(), mPos.z + (mPos.z + mHeight) / 2));
	c->flip();
	c->untap();
	c->mIsVisible[0] = false;
	c->mIsVisible[1] = false;
	mCards.push_back(c);
}

void Deck::shuffle()
{
	for (int i = 0; i < mCards.size(); i++)
	{
		int x = mRandomGen->Random(mCards.size());
		Card* tmp = mCards.at(x);
		mCards.at(x) = mCards.at(i);
		mCards.at(i) = tmp;
	}
}

//void Deck::loadFromFile(string s, int uid)
//{
//	cards.empty();
//	fstream file;
//	file.open(s, ios::in | ios::out);
//	string str;
//
//	int cnt = 0;
//	
//	while (!file.eof())
//	{
//		getline(file, str);
//		Card* c = new Card(uid+cnt, getCardIdFromName(str), owner);
//		addCard(c);
//		cnt++;
//	}
//
//	file.close();
//}
