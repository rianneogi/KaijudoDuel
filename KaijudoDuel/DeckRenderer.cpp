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
