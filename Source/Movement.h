#pragma once

#include "Camera.h"

struct Orientation
{
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	glm::vec3 right;
	glm::quat quat;
	Orientation() {}
	Orientation(glm::vec3 p, glm::vec3 d, glm::vec3 u) : pos(p), dir(d), up(u) 
	{
		calculateQuat();
	}
	void calculateQuat()
	{
		dir = glm::normalize(dir);
		up = glm::normalize(up);
		right = glm::cross(dir, up);
		up = glm::cross(right, dir);
		glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), dir);
		glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
		glm::quat rot2 = getRotationBetweenVectors(newUp, up);
		quat = rot2*frontq;
	}
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

