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
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION_VERT*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
}

void BattleZoneRenderer::updateCard(CardModel* model, Card* card, int pos, int size, int hovercard)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + mWidth - CONST_CARDSEPERATION_HORI*pos - CONST_CARDSEPERATION_HORI / 2, 
		mPos.y + 3*CONST_CARDTHICKNESS*card->evostack.size(), mPos.z + mHeight / 2);
	
	if(card->isTapped)
		o.dir = glm::vec3(-1, 0, 0);
	else
		o.dir = glm::vec3(0, 0, 1);

	if (hovercard == card->UniqueId)
	{
		o.pos = glm::vec3(gHighlightX, gHighlightY, gHighlightZ);
		o.dir = glm::vec3(0, 0, 1);
	}

	o.up = glm::vec3(0, 1, 0);
	o.calculateQuat();

	if (hovercard == card->UniqueId)
	{
		model->setHoverMovement(o, 1000);
	}
	else
	{
		model->setMovement(o, 1000);
	}
}
