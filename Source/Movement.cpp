#include "Movement.h"

Movement::Movement(): mTimeLeft(0)
{
}

Movement::Movement(Orientation curr, Orientation targ, int time) : mCurrent(curr), mTarget(targ), mTimeLeft(time)
{
}

Movement::~Movement()
{
}

void Movement::update(Orientation& newcurrent, int deltaTime)
{
	if (deltaTime > mTimeLeft)
	{
		mCurrent.pos = mTarget.pos;
	}
	else
	{
		glm::vec3 unitpos = (mTarget.pos - mCurrent.pos) / (float)mTimeLeft;
		mCurrent.pos += unitpos*(float)deltaTime;
	}

	mCurrent.dir = mTarget.dir;
	mCurrent.up = mTarget.up;
	mTimeLeft -= deltaTime;
	newcurrent = mCurrent;
}

bool Movement::isFinished()
{
	if (mTimeLeft > 0)
		return false;
	return true;
}