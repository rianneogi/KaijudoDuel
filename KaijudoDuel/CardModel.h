#pragma once

#include "LoadResources.h"
#include "Duel.h"

class CardModel
{
public:
	int mCardId;

	Model mFrontModel;
	Model mBackModel;

	Orientation mOrientation;
	glm::vec3 mHoverPos;
	/*glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::vec3 mUp;*/

	Movement mMovement;

	CardModel();
	CardModel(int cid);
	~CardModel();

	//void render(int myPlayer);
	//void update(int deltaTime);
	bool rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions);
	//void handleEvent(const SDL_Event& e);
	//void setPosition(glm::vec3 pos);
	//void move(Orientation target, int time);
	//void hover(Orientation target, int time);

	void render(bool visible);
	void setPosition(const glm::vec3& pos);
	void setDirection(const glm::vec3& dir);
	void setUp(const glm::vec3& up);
	void setMovement(Orientation target, int time);
	void setHoverMovement(Orientation target, int time);
	void update(int deltaTime);
	glm::mat4 getModelMatrix();
	glm::mat4 getHoverModelMatrix();
};

int loadCardTexture(const std::string& name, const std::string& set);

