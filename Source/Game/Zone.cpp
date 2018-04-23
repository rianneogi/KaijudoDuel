#include "Zone.h"

Zone::Zone()
{
}

//Zone::Zone(glm::vec3 p, float w, float h) : mPos(p), mWidth(w), mHeight(h)
//{
//}

Zone::~Zone()
{
	/*for (int i = 0; i < cards.size(); i++)
	{
		delete cards.at(i);
	}*/
}

void Zone::removeCard(Card* c)
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

//void Zone::render(sf::RenderWindow& window)
//{
//	window.draw(rect);
//}

//sf::FloatRect Zone::getBounds()
//{
//	return rect.getGlobalBounds();
//}
