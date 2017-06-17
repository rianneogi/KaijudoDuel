#include "DeckRenderer.h"

DeckRenderer::DeckRenderer()
{
}

DeckRenderer::~DeckRenderer()
{
}

void DeckRenderer::addCard(CardModel * c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*mCardModels.size(), mPos.z + (mPos.z + mHeight) / 2));
}

void DeckRenderer::updateCard(CardModel* c, int pos, int size)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + (mPos.x + mWidth) / 2, mPos.y + CONST_CARDTHICKNESS*pos, mPos.z + (mPos.z + mHeight) / 2);
	o.dir = glm::vec3(0, 0, 1);
	o.up = glm::vec3(0, -1, 0);
	o.calculateQuat();
	c->setMovement(o, 1000);
}