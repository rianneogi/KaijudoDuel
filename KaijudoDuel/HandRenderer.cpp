#include "HandRenderer.h"

HandRenderer::HandRenderer() : mCamera(NULL)
{
}

HandRenderer::~HandRenderer()
{
}

void HandRenderer::addCard(CardModel * c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
	update(-1);
}

void HandRenderer::updateCard(CardModel* c, int pos, int size)
{
	glm::vec3 center(mCamera->mPosition + mCamera->mDirection*gHandStraightDistance - gHandDownDistance*mCamera->mUp);
	glm::vec3 centerhover(mCamera->mPosition + mCamera->mDirection*gHandHoverStraightDistance - gHandHoverDownDistance*mCamera->mUp);

	float angle = M_PI / 2 + (M_PI / 8)*(float(size) / -2.f + pos);
	glm::vec3 dir(sin(angle)*mCamera->mUp - cos(angle)*mCamera->mRight);
	glm::vec3 offset(1.75f*dir - pos*0.1f*mCamera->mDirection);

	Orientation o;
	o.dir = mCamera->mUp + dir;
	o.up = -mCamera->mDirection;
	if (c->mUniqueId == mHoverCard)
	{
		o.pos = centerhover + offset;
		c->setHoverMovement(o, 1000);
	}
	else
	{
		o.pos = center + offset;
		c->setMovement(o, 1000);
	}
}

void HandRenderer::update(int hovercard)
{
	
}

void HandRenderer::setCamera(Camera* cam)
{
	mCamera = cam;
}
