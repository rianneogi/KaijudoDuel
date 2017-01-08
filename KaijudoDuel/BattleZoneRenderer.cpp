#include "BattleZoneRenderer.h"

BattleZoneRenderer::BattleZoneRenderer()
{
}

BattleZoneRenderer::~BattleZoneRenderer()
{
}

void BattleZoneRenderer::addCard(CardModel * c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
}
