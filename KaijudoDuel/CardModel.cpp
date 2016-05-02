#include "CardModel.h"

CardModel::CardModel() : mCardId(-1), mOrientation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0))
{
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];
}

CardModel::CardModel(int cid) : mCardId(cid), mOrientation(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0,1,0))
{
	mFrontModel.mTexture = gCardTextures[mCardId];
	mBackModel.mTexture = &gCardBackTexture;
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];
}

CardModel::~CardModel()
{
}

glm::mat4 CardModel::getModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mOrientation.pos);
	mOrientation.dir = glm::normalize(mOrientation.dir);
	mOrientation.up = glm::normalize(mOrientation.up);
	glm::vec3 right = glm::cross(mOrientation.dir, mOrientation.up);
	mOrientation.up = glm::cross(right, mOrientation.dir);
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mOrientation.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mOrientation.up);
	glm::mat4 frontrot = glm::toMat4(rot2*frontq);
	return (pos*frontrot);
}

void CardModel::render(bool visible)
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mOrientation.pos);

	if (visible)
	{
		assert(mCardId < gCardTextures.size());
		assert(mCardId >= 0);
		mFrontModel.mTexture = gCardTextures[mCardId];
	}
	else
	{
		mFrontModel.mTexture = &gCardBackTexture;
	}
	mOrientation.dir = glm::normalize(mOrientation.dir);
	mOrientation.up = glm::normalize(mOrientation.up);
	glm::vec3 right = glm::cross(mOrientation.dir, mOrientation.up);
	mOrientation.up = glm::cross(right, mOrientation.dir);

	//glm::mat4 front = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, mUp));
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mOrientation.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mOrientation.up);
	glm::mat4 frontrot = glm::toMat4(rot2*frontq);

	gShaders[gActiveShader].setUniformMat4f(0, pos*frontrot);
	mFrontModel.render();

	//glm::mat4 back = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, -mUp));
	glm::quat backq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mOrientation.dir);
	newUp = backq * glm::vec3(0.0f, 1.0f, 0.0f);
	rot2 = getRotationBetweenVectors(newUp, -mOrientation.up);
	glm::mat4 backrot = glm::toMat4(rot2*backq);

	gShaders[gActiveShader].setUniformMat4f(0, pos*backrot);
	mBackModel.render();
}

void CardModel::update(int deltaTime)
{
	if (!mMovement.isFinished())
	{
		mMovement.update(mOrientation, deltaTime);
	}
}

void CardModel::setMovement(Orientation target, int time)
{
	mMovement = Movement(mOrientation, target, time);
}

void CardModel::setPosition(const glm::vec3& pos)
{
	mOrientation.pos = pos;
}

void CardModel::setDirection(const glm::vec3& dir)
{
	mOrientation.dir = dir;
}

void CardModel::setUp(const glm::vec3& up)
{
	mOrientation.up = up;
}
