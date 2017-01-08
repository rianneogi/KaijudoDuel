#pragma once

#include "CardModel.h"

class ZoneRenderer
{
public:
	Zone* mZone;

	glm::vec3 mPos;
	float mWidth;
	float mHeight;

	ZoneRenderer();
	ZoneRenderer(Zone* zone);
	ZoneRenderer(Zone* zone, glm::vec3 pos, float w, float h);
	~ZoneRenderer();

	void renderCards(int myPlayer);
	bool rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions);
};

