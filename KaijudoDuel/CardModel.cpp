#include "CardModel.h"

CardModel::CardModel() : mCardId(-1), mRender(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0))
{
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];

	mMoveSpeed = 0.0005;
	mTurnSpeed = 0.00010;
}

CardModel::CardModel(int uid, int cid) : mUniqueId(uid), mCardId(cid), mRender(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0,1,0))
{
	mFrontModel.mTexture = gCardTextures[mCardId];
	mBackModel.mTexture = &gCardBackTexture;
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];

	mMoveSpeed = 0.0005;
	mTurnSpeed = 0.00015;
}

CardModel::~CardModel()
{
}

glm::mat4 CardModel::getModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mRender.pos);

	mRender.dir = glm::normalize(mRender.dir);
	mRender.up = glm::normalize(mRender.up);
	glm::vec3 right = glm::cross(mRender.dir, mRender.up);
	mRender.up = glm::cross(right, mRender.dir);
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mRender.up);
	glm::mat4 frontrot = glm::toMat4(rot2*frontq);

	return (pos*frontrot);
}

glm::mat4 CardModel::getHoverModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mCollision.pos);

	mCollision.dir = glm::normalize(mCollision.dir);
	mCollision.up = glm::normalize(mCollision.up);
	glm::vec3 right = glm::cross(mCollision.dir, mCollision.up);
	mCollision.up = glm::cross(right, mCollision.dir);
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mCollision.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mCollision.up);
	glm::mat4 frontrot = glm::toMat4(rot2*frontq);

	return (pos*frontrot);
}

void CardModel::flip()
{
	mTarget.up = glm::vec3(0, -1, 0);
}

void CardModel::unflip()
{
	mTarget.up = glm::vec3(0, 1, 0);
}

void CardModel::tap()
{
	mTarget.dir = glm::vec3(1, 0, 0);
}

void CardModel::untap()
{
	mTarget.dir = glm::vec3(0, 0, 1);
}

void CardModel::render(bool visible)
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mRender.pos);

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
	mRender.dir = glm::normalize(mRender.dir);
	mRender.up = glm::normalize(mRender.up);
	glm::vec3 right = glm::cross(mRender.dir, mRender.up);
	mRender.up = glm::cross(right, mRender.dir);

	//glm::mat4 front = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, mUp));
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mRender.up);
	glm::mat4 frontrot = glm::toMat4(rot2*frontq);

	gShaders[gActiveShader].setUniformMat4f(0, pos*frontrot);
	mFrontModel.render();

	//glm::mat4 back = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, -mUp));
	glm::quat backq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	newUp = backq * glm::vec3(0.0f, 1.0f, 0.0f);
	rot2 = getRotationBetweenVectors(newUp, -mRender.up);
	glm::mat4 backrot = glm::toMat4(rot2*backq);

	gShaders[gActiveShader].setUniformMat4f(0, pos*backrot);
	mBackModel.render();
}

void CardModel::update(int deltaTime)
{
	/*if (!mMovement.isFinished())
	{
		mMovement.update(mOrientation, deltaTime);
	}*/

	glm::vec3 unitpos = (mTarget.pos - mRender.pos) * (float)mMoveSpeed;
	mRender.pos += unitpos*(float)deltaTime;

	glm::vec3 unitdir = (mTarget.dir - mRender.dir) * (float)mTurnSpeed;
	mRender.dir += unitdir*(float)deltaTime;

	glm::vec3 unitup = (mTarget.up - mRender.up) * (float)mTurnSpeed;
	mRender.up += unitup*(float)deltaTime;
}

bool CardModel::rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions)
{
	Vector2f mousepixel;
	mousepixel.x = mousePos.x / (screenDimensions.x / 2.f) - 1.f;
	mousepixel.y = -(mousePos.y / (screenDimensions.y / 2.f) - 1.f);
	glm::mat4 finalmat = projview*getHoverModelMatrix();

	std::vector<glm::vec4> newverts;
	/*newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, 1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, 1.38f, 1));*/
	for (size_t i = 0; i < gMeshs[MESH_CARD].mEntries[0].mVertices.size(); i++)
	{
		Vector3f v = gMeshs[MESH_CARD].mEntries[0].mVertices[i].Pos;
		newverts.push_back(finalmat*glm::vec4(v.x, v.y, v.z, 1));
	}

	for (size_t i = 0; i < newverts.size(); i++) //perspective divide
	{
		newverts[i].x /= newverts[i].w;
		newverts[i].y /= newverts[i].w;
		newverts[i].z /= newverts[i].w;
	}

	if (isPointInsidePolygon(newverts, mousepixel.x, mousepixel.y))
	{
		return true;
	}
	return false;
}

void CardModel::setMovement(Orientation target, int time)
{
	//mMovement = Movement(mOrientation, target, time);
	//mHoverPos = target.pos;
	mTarget = target;
	mCollision = target;
}

void CardModel::setHoverMovement(Orientation target, int time)
{
	//mMovement = Movement(mOrientation, target, time);
	mTarget = target;
}

void CardModel::setOrientation(Orientation o)
{
	mRender = o;
	mTarget = o;
	mCollision = o;
}

void CardModel::setPosition(const glm::vec3& pos)
{
	mRender.pos = pos;
	mTarget.pos = pos;
	mCollision.pos = pos;
	//mHoverPos = pos;
}

void CardModel::setDirection(const glm::vec3& dir)
{
	//mOrientation.dir = dir;
	mRender.dir = dir;
	mTarget.dir = dir;
	mCollision.dir = dir;
}

void CardModel::setUp(const glm::vec3& up)
{
	//mOrientation.up = up;
	mRender.up = up;
	mTarget.up = up;
	mCollision.up = up;
}

int loadCardTexture(const std::string& name, const std::string& set)
{
	std::string path = "Resources\\Cards\\" + set + "\\" + name + ".png";
	gCardTextures.push_back(new Texture());
	if (!gCardTextures.at(gCardTextures.size() - 1)->loadFromFile(path))
	{
		//cout << "ERROR cant load texture " << CardNames.at(CardNames.size() - 1) << endl;
		printf("ERROR: cant load card texture %s\n", gCardNames.at(gCardNames.size() - 1).c_str());
	}
	//printf("Generated texture: %d\n", gCardTextures[gCardTextures.size() - 1]->mTextureID);
	//gCardTextures.at(gCardTextures.size() - 1).setSmooth(true);
	return 1;
}

bool initCardModels()
{
	for (size_t i = 0; i < CardDatabase.size(); i++)
	{
		loadCardTexture(CardDatabase[i].Name, CardDatabase[i].Set);
	}
	return true;
}

void cleanupCardModels()
{
	for (int i = 0;i < gCardTextures.size();i++)
	{
		delete gCardTextures[i];
	}
}
