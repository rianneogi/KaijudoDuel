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

void BattleZoneRenderer::updateCard(CardModel* c, int pos, int size)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + CONST_CARDSEPERATION*pos + CONST_CARDSEPERATION / 2, mPos.y, mPos.z + (mPos.z + mHeight) / 2);
	o.dir = c->mRender.dir;
	o.up = c->mRender.up;
	c->setMovement(o, 1000);
}
