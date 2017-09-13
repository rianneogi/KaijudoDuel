#include "GraveyardRenderer.h"

GraveyardRenderer::GraveyardRenderer() : mIsOpen(0), mScrollPos(0)
{
}

GraveyardRenderer::~GraveyardRenderer()
{
}

void GraveyardRenderer::addCard(CardModel* c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*mCardModels.size(), mPos.z + (mPos.z + mHeight) / 2));
}

void GraveyardRenderer::updateCard(CardModel* model, Card* card, int pos, int size, int hovercard)
{
	if (mIsOpen)
	{
		Orientation o;
		o.pos = glm::vec3(-2, 20 + CONST_CARDTHICKNESS*pos, -3 + mScrollPos + (size-pos-1)*0.4);
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
		o.pos = glm::vec3(mPos.x + mWidth / 2, mPos.y + CONST_CARDTHICKNESS*pos, mPos.z + mHeight / 2);
		o.dir = glm::vec3(0, 0, 1);
		o.up = glm::vec3(0, 1, 0);
		o.calculateQuat();
		model->setMovement(o, 1000);
	}
}
