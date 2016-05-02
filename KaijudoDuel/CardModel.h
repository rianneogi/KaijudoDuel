#pragma once

#include "Movement.h"

class CardModel
{
public:
	int mCardId;

	Model mFrontModel;
	Model mBackModel;

	Orientation mOrientation;
	/*glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::vec3 mUp;*/

	Movement mMovement;

	CardModel();
	CardModel(int cid);
	~CardModel();

	void render(bool visible);
	void setPosition(const glm::vec3& pos);
	void setDirection(const glm::vec3& dir);
	void setUp(const glm::vec3& up);
	void setMovement(Orientation target, int time);
	void update(int deltaTime);
	glm::mat4 getModelMatrix();
};

