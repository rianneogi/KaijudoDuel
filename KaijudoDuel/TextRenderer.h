#pragma once

#include "Model.h"

extern FT_Library gFontLibrary;
extern ShaderProgram gTextShader;

class TextRenderer
{
public:
	struct Character 
	{
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};
	std::map<GLchar, Character> mCharacters;

	FT_Face mFace;
	//GLuint mTextureID;
	GLuint mVAO;
	GLuint mVBO;
	int mSize;
	glm::vec4 mColor;

	TextRenderer();
	TextRenderer(std::string path, glm::vec4 color, int size);
	~TextRenderer();

	bool load(std::string path, glm::vec4 color, int size);
	void renderText(std::string text, float x, float y, float sx, float sy);
	void setSize(int size);
	void setColor(glm::vec4 color);
};

bool initTextRender();