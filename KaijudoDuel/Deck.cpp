#include "Deck.h"

Deck::Deck()
{
}

Deck::~Deck()
{
}

Card* Deck::draw()
{
	if (cards.size() == 0) return NULL;
	Card* c = cards.at(cards.size()-1);
	cards.pop_back();
	return c;
}

int Deck::getTopCard()
{
	return cards.at(cards.size() - 1)->UniqueId;
}

void Deck::renderCards(int myPlayer)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(myPlayer);
	}
}

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
	c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*cards.size(), mPos.z + (mPos.z + mHeight) / 2));
	c->flip();
	c->untap();
	cards.push_back(c);
}

void Deck::shuffle()
{
	for (int i = 0; i < cards.size(); i++)
	{
		int x = RandomGen->Random(cards.size());
		Card* tmp = cards.at(x);
		cards.at(x) = cards.at(i);
		cards.at(i) = tmp;
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