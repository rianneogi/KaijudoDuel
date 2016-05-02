#include "Zone.h"

Zone::Zone() : mPos(glm::vec3(0,0,0)), mWidth(0), mHeight(0)
{
}

Zone::Zone(glm::vec3 p, float w, float h) : mPos(p), mWidth(w), mHeight(h)
{
}

Zone::~Zone()
{
	/*for (int i = 0; i < cards.size(); i++)
	{
		delete cards.at(i);
	}*/
}

void Zone::removeCard(Card* c)
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

//void Zone::render(sf::RenderWindow& window)
//{
//	window.draw(rect);
//}

//sf::FloatRect Zone::getBounds()
//{
//	return rect.getGlobalBounds();
//}
