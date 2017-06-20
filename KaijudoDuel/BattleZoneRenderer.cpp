#include "BattleZoneRenderer.h"

BattleZoneRenderer::BattleZoneRenderer()
{
}

BattleZoneRenderer::~BattleZoneRenderer()
{
}

void BattleZoneRenderer::addCard(CardModel* c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
}

void BattleZoneRenderer::updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + mWidth - CONST_CARDSEPERATION*pos - CONST_CARDSEPERATION / 2, mPos.y, mPos.z + (mPos.z + mHeight) / 2);

	if(istapped)
		o.dir = glm::vec3(-1, 0, 0);
	else
		o.dir = glm::vec3(0, 0, 1);

	if (hovercard == c->mUniqueId)
		o.pos = glm::vec3(gHighlightX, gHighlightY, gHighlightZ);

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
