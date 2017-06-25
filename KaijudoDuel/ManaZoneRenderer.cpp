#include "ManaZoneRenderer.h"

ManaZoneRenderer::ManaZoneRenderer()
{
}

ManaZoneRenderer::~ManaZoneRenderer()
{
}

void ManaZoneRenderer::addCard(CardModel * c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION_VERT*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
}

void ManaZoneRenderer::updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + mWidth - CONST_CARDSEPERATION_HORI*pos - CONST_CARDSEPERATION_HORI / 2, mPos.y, mPos.z + mHeight / 2);

	if (istapped)
		o.dir = glm::vec3(1, 0, 0);
	else
		o.dir = glm::vec3(0, 0, -1);

	if (hovercard == c->mUniqueId)
	{
		o.pos = glm::vec3(gHighlightX, gHighlightY, gHighlightZ);
		o.dir = glm::vec3(0, 0, 1);
	}

	o.up = glm::vec3(0, 1, 0);
	o.calculateQuat();

	if (hovercard == c->mUniqueId)
	{
		c->setHoverMovement(o, 1000);
	}
	else
	{
		c->setMovement(o, 1000);
	}
}
