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

void GraveyardRenderer::updateCard(CardModel* c, int pos, int size, int hovercard, int istapped, int isflipped)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*pos, mPos.z + (mPos.z + mHeight) / 2);
	o.dir = glm::vec3(0, 0, 1);
	o.up = glm::vec3(0, 1, 0);
	o.calculateQuat();
	c->setMovement(o, 1000);
}
