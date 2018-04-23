#include "CardModel.h"

CardModel::CardModel() : mCardId(-1), mRender(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0))
{
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];

	mMoveSpeed = CONST_CARD_MOVESPEED;
	mTurnSpeed = CONST_CARD_TURNSPEED;
}

CardModel::CardModel(int uid, int cid) : mUniqueId(uid), mCardId(cid), mRender(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0,1,0))
{
	mFrontModel.mTexture = gCardTextures[mCardId];
	mBackModel.mTexture = &gCardBackTexture;
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];

	mMoveSpeed = CONST_CARD_MOVESPEED;
	mTurnSpeed = CONST_CARD_TURNSPEED;
}

CardModel::~CardModel()
{
}

glm::mat4 CardModel::getModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mRender.pos);

	/*mRender.dir = glm::normalize(mRender.dir);
	mRender.up = glm::normalize(mRender.up);
	glm::vec3 right = glm::cross(mRender.dir, mRender.up);
	mRender.up = glm::cross(right, mRender.dir);
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mRender.up);*/
	glm::mat4 frontrot = glm::toMat4(mRender.quat);

	return (pos*frontrot);
}

glm::mat4 CardModel::getHoverModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mCollision.pos);

	/*mCollision.dir = glm::normalize(mCollision.dir);
	mCollision.up = glm::normalize(mCollision.up);
	glm::vec3 right = glm::cross(mCollision.dir, mCollision.up);
	mCollision.up = glm::cross(right, mCollision.dir);
	glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mCollision.dir);
	glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = getRotationBetweenVectors(newUp, mCollision.up);*/
	glm::mat4 frontrot = glm::toMat4(mCollision.quat);

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
	//mRender.dir = glm::normalize(mRender.dir);
	//mRender.up = glm::normalize(mRender.up);
	//glm::vec3 right = glm::cross(mRender.dir, mRender.up);
	//mRender.up = glm::cross(right, mRender.dir);

	//glm::mat4 front = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, mUp));
	//glm::quat frontq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	//glm::vec3 newUp = frontq * glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::quat rot2 = getRotationBetweenVectors(newUp, mRender.up);
	glm::mat4 frontrot = glm::toMat4(mRender.quat);

	gShaders[gActiveShader].setUniformMat4f(0, pos*frontrot);
	mFrontModel.render();

	//glm::mat4 back = (glm::lookAt(glm::vec3(0, 0, 0), -mDirection, -mUp));
	//glm::quat backq = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
	//newUp = backq * glm::vec3(0.0f, 1.0f, 0.0f);
	//rot2 = getRotationBetweenVectors(newUp, -mRender.up);
	glm::mat4 backrot = glm::toMat4(glm::rotate(mRender.quat, float(M_PI), glm::vec3(0, 0, 1)));

	gShaders[gActiveShader].setUniformMat4f(0, pos*backrot);
	mBackModel.render();
}

void CardModel::renderAttachedText(const std::string& str, glm::vec4 color, TextRenderer& renderer, const glm::mat4& V, const glm::mat4& P)
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mRender.pos);
	glm::mat4 frontrot = glm::toMat4(glm::rotate(mRender.quat, float(M_PI), glm::vec3(0, 1, 0)));

	renderer.setColor(color);
	renderer.renderTextMVP(str, -0.5, -1.5, 30.0 / SCREEN_WIDTH, 30.0 / SCREEN_HEIGHT, pos*frontrot, V, P);
}

void CardModel::update(int deltaTime)
{
	/*if (!mMovement.isFinished())
	{
		mMovement.update(mOrientation, deltaTime);
	}*/

	glm::vec3 unitpos = (mTarget.pos - mRender.pos) * (float)mMoveSpeed;
	mRender.pos += unitpos*(float)deltaTime;

	//glm::vec3 unitdir = (mTarget.dir - mRender.dir) * (float)mTurnSpeed;
	//mRender.dir += unitdir*(float)deltaTime;

	//mRender.dir = glm::mix(mRender.dir, mTarget.dir, deltaTime*mTurnSpeed);

	//glm::vec3 unitup = (mTarget.up - mRender.up) * (float)mTurnSpeed;
	//mRender.up += unitup*(float)deltaTime;
	//mRender.up = glm::mix(mRender.up, mTarget.up, deltaTime*mTurnSpeed);

	//printf("dir %f %f %f\n", mRender.dir.x, mRender.dir.y, mRender.dir.z);
	//printf("up %f %f %f\n", mRender.up.x, mRender.up.y, mRender.up.z);

	/*if (glm::length(mTarget.dir - mRender.dir) <= 0.1 && glm::length(mTarget.up - mRender.up) <= 0.1)
	{
		mRender.dir = mTarget.dir;
		mRender.up = mTarget.up;
	}
	else
	{*/
		/*glm::quat tq1 = getRotationBetweenVectors(glm::vec3(0, 0, 1), mTarget.dir);
		glm::vec3 newUp = tq1*glm::vec3(0, 1, 0);
		glm::quat tq2 = getRotationBetweenVectors(newUp, mTarget.up);
		glm::quat tq = tq2*tq1;

		glm::quat sq1 = getRotationBetweenVectors(glm::vec3(0, 0, 1), mRender.dir);
		newUp = sq1*glm::vec3(0, 1, 0);
		glm::quat sq2 = getRotationBetweenVectors(newUp, mRender.up);
		glm::quat sq = sq2*sq1;*/

		mRender.quat = glm::slerp(mRender.quat, mTarget.quat, deltaTime*mTurnSpeed);
	//}
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
	mRender.calculateQuat();
	mTarget.calculateQuat();
	mCollision.calculateQuat();
}

void CardModel::setUp(const glm::vec3& up)
{
	//mOrientation.up = up;
	mRender.up = up;
	mTarget.up = up;
	mCollision.up = up;
	mRender.calculateQuat();
	mTarget.calculateQuat();
	mCollision.calculateQuat();
}

int loadCardTexture(const std::string& name, const std::string& set)
{
	std::string path = "Resources/Cards/Textures/Sets/" + set + "/Cards/" + name + ".jpg";
	gCardTextures.push_back(new Texture());
	if (!gCardTextures.at(gCardTextures.size() - 1)->loadFromFile(path))
	{
		//cout << "ERROR cant load texture " << CardNames.at(CardNames.size() - 1) << endl;
		printf("ERROR: cant load card texture %s\n", gCardDatabase[gCardTextures.size() - 1].Name.c_str());
	}
	//printf("Generated texture: %d\n", gCardTextures[gCardTextures.size() - 1]->mTextureID);
	//gCardTextures.at(gCardTextures.size() - 1).setSmooth(true);
	return 1;
}

bool initCardModels()
{
	for (size_t i = 0; i < gCardDatabase.size(); i++)
	{
		loadCardTexture(gCardDatabase[i].Name, gCardDatabase[i].Set);
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
