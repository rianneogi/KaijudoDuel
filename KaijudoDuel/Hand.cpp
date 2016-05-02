#include "Hand.h"

Hand::Hand() : myPlayer(0)
{
}

Hand::Hand(int p) : myPlayer(p)
{
}


Hand::~Hand()
{
}

void Hand::renderCards(int myPlayer)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(myPlayer);
	}
}

void Hand::update(const Camera& camera, int hovercard)
{
	const float straight = 10.f;
	const float down = 5.f;
	const float hoverstraight = 4.f;
	const float hoverdown = 2.f;
	glm::vec3 center(camera.mPosition + camera.mDirection*straight - down*camera.mUp);
	glm::vec3 centerhover(camera.mPosition + camera.mDirection*hoverstraight - hoverdown*camera.mUp);
	for (int i = 0; i < cards.size(); i++)
	{
		float angle = M_PI/2 + (M_PI/8)*(float(cards.size())/-2.f + i);
		glm::vec3 dir(sin(angle)*camera.mUp - cos(angle)*camera.mRight);
		glm::vec3 offset(1.75f*dir - i*0.1f*camera.mDirection);

		Orientation o;
		o.dir = camera.mUp + dir;
		o.up = -camera.mDirection;
		if (cards.at(i)->UniqueId == hovercard)
		{
			o.pos = centerhover + offset;
		}
		else
		{
			o.pos = center + offset;
		}
		cards.at(i)->move(o, 1000);
	}
}

//
//void Hand::handleEvent(sf::Event event)
//{
//	for (int i = 0; i < cards.size(); i++)
//	{
//		cards.at(i)->handleEvent(event);
//	}
//}

void Hand::addCard(Card* c)
{
	//c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	//c->unflipForPlayer(c->Owner);
	//c->flipForPlayer(getOpponent(c->Owner));
	//if (c->Owner == myPlayer)
	//{
	//	c->unflip();
	//}
	//else
	//{
	//	c->flip();
	//}
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*cards.size(), mPos.y, mPos.z + (mPos.z+mHeight)/2));
	c->unflip();
	c->untap();
	cards.push_back(c);
}

void Hand::removeCard(Card* c)
{
	int x = 0;
	for (std::vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if (*i == c)
		{
			cards.erase(i);
			break;
		}
		x++;
	}
	for (int i = x; i < cards.size(); i++)
	{
		//cards.at(i)->setPosition(cards.at(i)->x - CARDSEPERATION, cards.at(i)->y);
	}
}

void Hand::flipAllCards()
{
	for (int j = 0; j < 2; j++)
	{
		for (std::vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
		{
			if ((*i)->isFlipped == true)
			{
				(*i)->unflip();
			}
			else
			{
				(*i)->flip();
			}
		}
	}
}
