#include "DeckRenderer.h"

DeckRenderer::DeckRenderer() : mIsOpen(0), mScrollPos(0)
{
}

DeckRenderer::~DeckRenderer()
{
}

void DeckRenderer::addCard(CardModel* c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*mCardModels.size(), mPos.z + (mPos.z + mHeight) / 2));
}

void DeckRenderer::updateCard(CardModel* model, Card* card, int pos, int size, int hovercard)
{
	if (mIsOpen)
	{
		Orientation o;
		o.pos = glm::vec3(-2, 20 + CONST_CARDTHICKNESS*(size-pos-1), -3 + mScrollPos + pos*0.4);
		if (card->mUniqueId == hovercard)
		{
			o.pos.y += 1;
		}
		o.dir = glm::vec3(0, 0, 1);
		o.up = glm::vec3(0, 1, 0);
		o.calculateQuat();
		if (card->mUniqueId == hovercard)
		{
			model->setHoverMovement(o, 1000);
		}
		else
		{
			model->setMovement(o, 1000);
		}
	}
	else
	{
		Orientation o;
		o.pos = glm::vec3(mPos.x + mWidth / 2, mPos.y + CONST_CARDTHICKNESS*1.5*pos, mPos.z + mHeight / 2);
		o.dir = glm::vec3(0, 0, 1);
		o.up = glm::vec3(0, -1, 0);
		o.calculateQuat();
		model->setMovement(o, 1000);
	}
}
