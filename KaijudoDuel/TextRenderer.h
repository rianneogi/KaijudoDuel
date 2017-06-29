#pragma once

#include "Model.h"

extern FT_Library gFontLibrary;
extern ShaderProgram gTextShader;

class TextRenderer
{
public:
	FT_Face mFace;
	GLuint mTextureID;
	GLuint mVBO;
	int mSize;
	glm::vec4 mColor;

	TextRenderer();
	TextRenderer(std::string path, glm::vec4 color, int size);
	~TextRenderer();

	bool load(std::string path, glm::vec4 color, int size);
	void renderText(const char *text, float x, float y, float sx, float sy);
	void setSize(int size);
	void setColor(glm::vec4 color);
};

bool initTextRender();