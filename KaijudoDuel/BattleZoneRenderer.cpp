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
		mPos.y + 3 * CONST_CARDTHICKNESS*card->mEvoStack.size(), mPos.z + mHeight / 2);

	for (size_t i = 0; i < card->mEvoStack.size(); i++)
	{
		if (card->mEvoStack[i]->mUniqueId == model->mUniqueId)
		{
			o.pos.y -= 3 * CONST_CARDTHICKNESS*(i+1);
		}
	}
	
	if(card->mIsTapped)
		o.dir = glm::vec3(-1, 0, 0);
	else
		o.dir = glm::vec3(0, 0, 1);

	if (hovercard == card->mUniqueId && card->mUniqueId == model->mUniqueId)
	{
		o.pos = glm::vec3(gHighlightX, gHighlightY, gHighlightZ);
		o.dir = glm::vec3(0, 0, 1);
	}

	o.up = glm::vec3(0, 1, 0);
	o.calculateQuat();

	if (hovercard == card->mUniqueId)
	{
		model->setHoverMovement(o, 1000);
	}
	else
	{
		model->setMovement(o, 1000);
	}
}
