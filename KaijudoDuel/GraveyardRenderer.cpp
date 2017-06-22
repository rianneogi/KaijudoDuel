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

void GraveyardRenderer::updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped)
{
	if (mIsOpen)
	{
		Orientation o;
		o.pos = glm::vec3(-2, 20 + CONST_CARDTHICKNESS*(size - pos - 1), -3 + mScrollPos + pos*0.4);
		if (c->mUniqueId == hovercard)
		{
			o.pos.y += 1;
		}
		o.dir = glm::vec3(0, 0, 1);
		o.up = glm::vec3(0, 1, 0);
		o.calculateQuat();
		if (c->mUniqueId == hovercard)
		{
			c->setHoverMovement(o, 1000);
		}
		else
		{
			c->setMovement(o, 1000);
		}
	}
	else
	{
		Orientation o;
		o.pos = glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*pos, mPos.z + (mPos.z + mHeight) / 2);
		o.dir = glm::vec3(0, 0, 1);
		o.up = glm::vec3(0, 1, 0);
		o.calculateQuat();
		c->setMovement(o, 1000);
	}
}
