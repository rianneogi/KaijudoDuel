#include "TextRenderer.h"

FT_Library gFontLibrary;
ShaderProgram gTextShader;

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
	glGenBuffers(1, &mVBO);
	return true;
}

void TextRenderer::renderText(const char *text, float x, float y, float sx, float sy)
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	
	//glUniform1i(uniform_tex, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	const char *p;
	gTextShader.bind();
	gTextShader.setUniformVec4f(0, mColor);
	gTextShader.setUniformInt(1, 0);


	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, mTextureID);

	//glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	for (p = text; *p; p++) 
	{
		if (FT_Load_Char(mFace, *p, FT_LOAD_RENDER))
		{
			printf("ERROR: loading character %c\n", *p);
			continue;
		}

		printf("char %c\n", *p);
		for (int i = 0; i < mFace->glyph->bitmap.width*mFace->glyph->bitmap.rows; i++)
		{
			printf("%f ", mFace->glyph->bitmap.buffer[i]);
			if (i&mFace->glyph->bitmap.width == 0)
				printf("\n");
		}

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

		float x2 = x + mFace->glyph->bitmap_left * sx;
		float y2 = -y - mFace->glyph->bitmap_top * sy;
		float w = mFace->glyph->bitmap.width * sx;
		float h = mFace->glyph->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (mFace->glyph->advance.x / 64) * sx;
		y += (mFace->glyph->advance.y / 64) * sy;
	}

	glDisableVertexAttribArray(0);
	glDeleteTextures(1, &mTextureID);

	GLenum err = GL_NO_ERROR;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		printf("TEXT DRAW ERROR: %d", err);
	}
}

bool initTextRender()
{
	if (FT_Init_FreeType(&gFontLibrary)) 
	{
		printf("Could not init freetype library\n");
		return false;
	}

	if (!gTextShader.loadProgram("Resources/Shaders/mvp"))
	{
		printf("ERROR: Could not load text shader\n");
		return false;
	}
	gTextShader.setMaxUniforms(2);
	gTextShader.addUniform("text_color");
	gTextShader.addUniform("texture");
	
	return true;
}
