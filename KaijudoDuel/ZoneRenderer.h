#pragma once

#include "CardModel.h"

class ZoneRenderer
{
public:
	//Zone* mZone;
	std::vector<CardModel*> mCardModels;
	//std::vector<CardModel*>* mCardModels;

	glm::vec3 mPos;
	float mWidth;
	float mHeight;

	ZoneRenderer();
	//ZoneRenderer(Zone* zone, std::vector<CardModel*>* models);
	//ZoneRenderer(Zone* zone, std::vector<CardModel*>* models, glm::vec3 pos, float w, float h);
	~ZoneRenderer();

	void renderCards(int myPlayer);
	bool rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions);

	virtual void addCard(CardModel* c) = 0;
	virtual void removeCard(CardModel* c);
	virtual void updateCard(CardModel* c, int pos, int size) = 0;
};



