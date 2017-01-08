#include "CardModel.h"

CardModel::CardModel() : mCardId(-1), mOrientation(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0))
{
	mFrontModel.mMesh = &gMeshs[MESH_CARD];
	mBackModel.mMesh = &gMeshs[MESH_CARD];
}

CardModel::CardModel(int uid, int cid) : mUniqueId(uid), mCardId(cid), mOrientation(glm::vec3(0,0,0), glm::vec3(0, 0, 1), glm::vec3(0,1,0))
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

glm::mat4 CardModel::getHoverModelMatrix()
{
	glm::mat4 pos = glm::translate(glm::mat4(1.0f), mHoverPos);

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

void CardModel::flip()
{
	mOrientation.up = glm::vec3(0, -1, 0);
}

void CardModel::unflip()
{
	mOrientation.up = glm::vec3(0, 1, 0);
}

void CardModel::tap()
{
	mOrientation.dir = glm::vec3(1, 0, 0);
}

void CardModel::untap()
{
	mOrientation.dir = glm::vec3(0, 0, 1);
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

bool CardModel::rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions)
{
	Vector2f mousepixel;
	mousepixel.x = mousePos.x / (screenDimensions.x / 2.f) - 1.f;
	mousepixel.y = -(mousePos.y / (screenDimensions.y / 2.f) - 1.f);
	glm::mat4 finalmat = projview*getHoverModelMatrix();

	std::vector<glm::vec4> newverts;
	newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, 1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, 1.38f, 1));

	for (int i = 0; i < 4; i++) //perspective divide
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
	mMovement = Movement(mOrientation, target, time);
	mHoverPos = target.pos;
}

void CardModel::setHoverMovement(Orientation target, int time)
{
	mMovement = Movement(mOrientation, target, time);
}

void CardModel::setPosition(const glm::vec3& pos)
{
	mOrientation.pos = pos;
	mHoverPos = pos;
}

void CardModel::setDirection(const glm::vec3& dir)
{
	mOrientation.dir = dir;
}

void CardModel::setUp(const glm::vec3& up)
{
	mOrientation.up = up;
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