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

void ShieldZoneRenderer::updateCard(CardModel* c, int pos, int size)
{
	Orientation o;
	o.pos = glm::vec3(mPos.x + CONST_CARDSEPERATION*pos + CONST_CARDSEPERATION / 2, mPos.y, mPos.z + (mPos.z + mHeight) / 2);
	o.dir = glm::vec3(0, 0, 1);
	o.up = glm::vec3(0, -1, 0);
	o.calculateQuat();
	c->setMovement(o, 1000);
}
