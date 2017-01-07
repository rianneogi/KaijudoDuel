#pragma once

#include "Camera.h"

struct Orientation
{
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	Orientation() {}
	Orientation(glm::vec3 p, glm::vec3 d, glm::vec3 u) :pos(p), dir(d), up(u) {}
};

class Movement
{
public:
	Orientation mCurrent;
	Orientation mTarget;
	int mTimeLeft;

	Movement();
	Movement(Orientation curr, Orientation targ, int time);
	~Movement();

	void update(Orientation& newcurrent, int deltaTime);
	bool isFinished();
};

