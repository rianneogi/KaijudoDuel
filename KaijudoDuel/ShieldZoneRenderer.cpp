#include "ShieldZoneRenderer.h"

ShieldZoneRenderer::ShieldZoneRenderer()
{
}

ShieldZoneRenderer::~ShieldZoneRenderer()
{
}

void ShieldZoneRenderer::addCard(CardModel * c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*mCardModels.size() + CONST_CARDSEPERATION / 2, mPos.y, mPos.z + (mPos.z + mHeight) / 2));
}
