#include "TextRenderer.h"

FT_Library gFontLibrary;
ShaderProgram gTextShader;
ShaderProgram gTextMVPShader;

TextRenderer::TextRenderer()
{
}

TextRenderer::TextRenderer(std::string path, glm::vec4 color, int size)
{
	load(path, color, size);
}

TextRenderer::~TextRenderer()
{
	FT_Done_Face(mFace);
	for (auto i = mCharacters.begin(); i != mCharacters.end(); i++)
	{
		glDeleteTextures(1, &(i->second.TextureID));
	}
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
}

void TextRenderer::setSize(int size)
{
	mSize = size;
	FT_Set_Pixel_Sizes(mFace, 0, size);
}

void TextRenderer::setColor(glm::vec4 color)
{
	mColor = color;
}

bool TextRenderer::load(std::string path, glm::vec4 color, int size)
{
	/*int fsize;
	char* font = readFile(path.c_str(), &fsize);
	if (font = NULL)
	{
		printf("Could not open font %s\n", path.c_str());
		return false;
	}
	FT_Error fterr = FT_New_Memory_Face(gFontLibrary, (FT_Byte*)font, fsize, 0, &mFace);
	if (fterr != FT_Err_Ok) 
	{
		printf("Could not init font: error %d\n", fterr);
		return false;
	}*/


	if (FT_New_Face(gFontLibrary, path.c_str(), 0, &mFace))
	{
		printf("Could not open font %s\n", path.c_str());
		return false;
	}

	mColor = color;
	setSize(size);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(mFace, c, FT_LOAD_RENDER))
		{
			printf("ERROR::FREETYTPE: Failed to load Glyph %c\n", c);
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			mFace->glyph->bitmap.width,
			mFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			mFace->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(mFace->glyph->bitmap.width, mFace->glyph->bitmap.rows),
			glm::ivec2(mFace->glyph->bitmap_left, mFace->glyph->bitmap_top),
			mFace->glyph->advance.x
		};
		mCharacters.insert(std::pair<GLchar, Character>(c, character));
	}

	//GLuint VAO, VBO;
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

//void TextRenderer::renderText(std::string text, float x, float y, float sx, float sy)
//{
//	glActiveTexture(GL_TEXTURE0);
//	glGenTextures(1, &mTextureID);
//	glBindTexture(GL_TEXTURE_2D, mTextureID);
//	
//	//glUniform1i(uniform_tex, 0);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
//
//	gTextShader.bind();
//	gTextShader.setUniformVec4f(0, mColor);
//	//gTextShader.setUniformInt(1, 0);
//
//	//glActiveTexture(GL_TEXTURE0);
//	//glBindTexture(GL_TEXTURE_2D, mTextureID);
//
//	//glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//
//	std::string::const_iterator c;
//	for (c = text.begin(); c != text.end(); c++)
//	{
//		if (FT_Load_Char(mFace, *c, FT_LOAD_RENDER))
//		{
//			printf("ERROR: loading character %c\n", *c);
//			continue;
//		}
//
//		printf("char %c\n", *c);
//		/*printf("ptr %d\n", mFace->glyph->bitmap.buffer);
//		for (int i = 0; i < mFace->glyph->bitmap.width*mFace->glyph->bitmap.rows; i++)
//		{
//			printf("%d ", mFace->glyph->bitmap.buffer[i]);
//			if (i&mFace->glyph->bitmap.width == 0)
//				printf("\n");
//		}*/
//
//		glTexImage2D(
//			GL_TEXTURE_2D,
//			0,
//			GL_RED,
//			mFace->glyph->bitmap.width,
//			mFace->glyph->bitmap.rows,
//			0,
//			GL_RED,
//			GL_UNSIGNED_BYTE,
//			mFace->glyph->bitmap.buffer
//		);
//
//		float x2 = x + mFace->glyph->bitmap_left * sx;
//		float y2 = -y - mFace->glyph->bitmap_top * sy;
//		float w = mFace->glyph->bitmap.width * sx;
//		float h = mFace->glyph->bitmap.rows * sy;
//
//		GLfloat box[4][4] = {
//			{ x2,     -y2    , 0, 0 },
//			{ x2 + w, -y2    , 1, 0 },
//			{ x2,     -y2 - h, 0, 1 },
//			{ x2 + w, -y2 - h, 1, 1 },
//		};
//
//		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//		/*GLenum err = GL_NO_ERROR;
//		while ((err = glGetError()) != GL_NO_ERROR)
//		{
//			printf("TEXT DRAW ERROR: %d", err);
//		}*/
//		
//		x += (mFace->glyph->advance.x / 64) * sx;
//		y += (mFace->glyph->advance.y / 64) * sy;
//	}
//
//	glDisableVertexAttribArray(0);
//	glDeleteTextures(1, &mTextureID);
//
//	GLenum err = GL_NO_ERROR;
//	while ((err = glGetError()) != GL_NO_ERROR)
//	{
//		printf("TEXT DRAW ERROR: %d", err);
//	}
//}

void TextRenderer::renderText(std::string text, float x, float y, float sx, float sy)
{
	// Activate corresponding render state	
	gTextShader.bind();
	//glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
	gTextShader.setUniformVec4f(0, mColor);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = mCharacters[*c];

		GLfloat xpos = x + ch.Bearing.x * sx;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * sy;

		GLfloat w = ch.Size.x * sx;
		GLfloat h = ch.Size.y * sy;
		
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * sx; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::renderTextMVP(std::string text, float x, float y, float sx, float sy, const glm::mat4& M, const glm::mat4& V, const glm::mat4& P) 
{
	// Activate corresponding render state	
	gTextMVPShader.bind();
	//glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);
	gTextMVPShader.setUniformVec4f(3, mColor);
	gTextMVPShader.setUniformMat4f(0, M);
	gTextMVPShader.setUniformMat4f(1, V);
	gTextMVPShader.setUniformMat4f(2, P);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAO);

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = mCharacters[*c];

		GLfloat xpos = x + ch.Bearing.x * sx;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * sy;

		GLfloat w = ch.Size.x * sx;
		GLfloat h = ch.Size.y * sy;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * sx; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool initTextRender()
{
	if (FT_Init_FreeType(&gFontLibrary)) 
	{
		printf("Could not init freetype library\n");
		return false;
	}

	if (!gTextShader.loadProgram("Resources/Shaders/text"))
	{
		printf("ERROR: Could not load text shader\n");
		return false;
	}
	gTextShader.setMaxUniforms(1);
	gTextShader.addUniform("text_color");
	//gTextShader.addUniform("texture");

	if (!gTextMVPShader.loadProgram("Resources/Shaders/text_mvp"))
	{
		printf("ERROR: Could not load text shader\n");
		return false;
	}
	gTextMVPShader.setMaxUniforms(4);
	gTextMVPShader.addUniform("M");
	gTextMVPShader.addUniform("V");
	gTextMVPShader.addUniform("P");
	gTextMVPShader.addUniform("text_color");
	//gTextShader.addUniform("texture");
	
	return true;
}
