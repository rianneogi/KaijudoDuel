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

bool Zone::rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions)
{
	Vector2f mousepixel;
	mousepixel.x = mousePos.x / (screenDimensions.x / 2.f) - 1.f;
	mousepixel.y = -(mousePos.y / (screenDimensions.y / 2.f) - 1.f);
	glm::mat4 finalmat = projview*glm::translate(glm::mat4(1.0), mPos);

	std::vector<glm::vec4> newverts;
	newverts.push_back(finalmat*glm::vec4(-mWidth, 0.f, -mHeight, 1));
	newverts.push_back(finalmat*glm::vec4(mWidth, 0.f, -mHeight, 1));
	newverts.push_back(finalmat*glm::vec4(mWidth, 0.f, mHeight, 1));
	newverts.push_back(finalmat*glm::vec4(-mWidth, 0.f, mHeight, 1));

	for (int i = 0;i < 4;i++) //perspective divide
	{
		newverts[i].x /= newverts[i].w;
		newverts[i].y /= newverts[i].w;
		newverts[i].z /= newverts[i].w;
	}

	if (isPointInsidePolygon(newverts, mousepixel.x, mousepixel.y))
	{
		return true;
	}
	return false;
}

//void Zone::render(sf::RenderWindow& window)
//{
//	window.draw(rect);
//}

//sf::FloatRect Zone::getBounds()
//{
//	return rect.getGlobalBounds();
//}
