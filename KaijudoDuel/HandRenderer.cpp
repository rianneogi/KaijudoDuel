#include "HandRenderer.h"

HandRenderer::HandRenderer(int owner) : mCamera(NULL), mOwner(owner), mCastingCard(-1)
{
}

HandRenderer::~HandRenderer()
{
}

void HandRenderer::addCard(CardModel* c)
{
	mCardModels.push_back(c);
	c->setPosition(glm::vec3(mPos.x + CONST_CARDSEPERATION_VERT*mCardModels.size(), mPos.y, mPos.z + (mPos.z + mHeight) / 2));
	update(-1);
}

void HandRenderer::updateCard(CardModel* model, Card* card, int pos, int size, int hovercard)
{
	if (card->mUniqueId == mCastingCard)
	{
		Orientation o;
		o.dir = mCamera->mUp;
		o.up = -mCamera->mDirection;

		if (hovercard == mCastingCard)
		{
			o.pos = glm::vec3(gHighlightX, gHighlightY, gHighlightZ);
		}
		else
		{
			o.pos = glm::vec3(gCastingCardX, gCastingCardY, gCastingCardZ);
		}
		o.calculateQuat();
		model->setMovement(o, 1000);
	}
	else if (mOwner == 0)
	{
		glm::vec3 center(mCamera->mPosition + mCamera->mDirection*gHandStraightDistance - 
			gHandDownDistance*mCamera->mUp + mCamera->mRight*gHandRightDistance);
		glm::vec3 centerhover(mCamera->mPosition + mCamera->mDirection*gHandHoverStraightDistance - 
			gHandHoverDownDistance*mCamera->mUp + mCamera->mRight*gHandHoverRightDistance);

		float angle = M_PI / 2 + (M_PI / 8)*(float(size) / -2.f + pos);
		glm::vec3 dir(sin(angle)*mCamera->mUp - cos(angle)*mCamera->mRight);
		glm::vec3 offset(1.75f*dir - pos*0.1f*mCamera->mDirection);

		Orientation o;
		o.dir = mCamera->mUp + dir;
		if (mTurn == mOwner)
			o.up = -mCamera->mDirection;
		else
		{
			o.up = mCamera->mDirection;
			o.dir.x *= -1;
		}
		if (card->mUniqueId == hovercard && mTurn == mOwner)
		{
			o.pos = centerhover + offset;
			o.calculateQuat();
			model->setHoverMovement(o, 1000);
		}
		else
		{
			o.pos = center + offset;
			o.calculateQuat();
			model->setMovement(o, 1000);
		}
	}
	else
	{
		glm::vec3 center(mCamera->mPosition + mCamera->mDirection*gHandStraightDistance +
			gHandDownDistance*mCamera->mUp + mCamera->mRight*gHandRightDistance);
		glm::vec3 centerhover(mCamera->mPosition + mCamera->mDirection*gHandHoverStraightDistance +
			gHandHoverDownDistance*mCamera->mUp + mCamera->mRight*gHandHoverRightDistance);

		float angle = M_PI / 2 + (M_PI / 8)*(float(size) / -2.f + pos);
		glm::vec3 dir(sin(angle)*mCamera->mUp - cos(angle)*mCamera->mRight);
		glm::vec3 offset(-1.75f*dir - pos*0.1f*mCamera->mDirection);

		Orientation o;
		o.dir = -mCamera->mUp - dir;
		if (mTurn == mOwner)
			o.up = -mCamera->mDirection;
		else
		{
			o.up = mCamera->mDirection;
			o.dir.x *= -1;
		}
		if (card->mUniqueId == hovercard && mTurn == mOwner)
		{
			o.dir = glm::vec3(0, 0, 1);
			o.up = glm::vec3(0, 1, 0);
			o.pos = centerhover + offset;
			o.calculateQuat();
			model->setHoverMovement(o, 1000);
		}
		else
		{
			o.pos = center + offset;
			o.calculateQuat();
			model->setMovement(o, 1000);
		}
	}
}

void HandRenderer::update(int hovercard)
{
	
}

void HandRenderer::setCamera(Camera* cam)
{
	mCamera = cam;
}
