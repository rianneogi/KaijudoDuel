#include "GraveyardRenderer.h"

GraveyardRenderer::GraveyardRenderer()
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

void GraveyardRenderer::updateCard(CardModel* c, int pos, int size)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*pos, mPos.z + (mPos.z + mHeight) / 2);
	o.dir = c->mRender.dir;
	o.up = c->mRender.up;
	c->setMovement(o, 1000);
}
