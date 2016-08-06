#include "LoadResources.h"

Texture gTableTexture;
Texture gCardBackTexture;
std::vector<Mesh> gMeshs;
std::vector<ShaderProgram> gShaders;
std::vector<Texture*> gCardTextures;

bool loadTextures()
{
	if (!gTableTexture.loadFromFile("Resources/Textures/woodsample.jpg"))
	{
		printf("ERROR: Could not load table texture\n");
		return false;
	}
	if (!gCardBackTexture.loadFromFile("Resources/cardback.png"))
	{
		printf("ERROR: Could not load cardback texture\n");
		return false;
	}
	return true;
}

bool loadMeshs()
{
	gMeshs.resize(MESH_NB);
	if (!gMeshs[MESH_CARD].loadFromFile("Resources/Meshs/card.obj"))
	{
		printf("ERROR: Could not load mesh\n");
		return false;
	}
	if (!gMeshs[MESH_TABLE].loadFromFile("Resources/Meshs/table.obj"))
	{
		printf("ERROR: Could not load table\n");
		return false;
	}
	if (!gMeshs[MESH_ENDTURN].loadFromFile("Resources/Meshs/endturn.obj"))
	{
		printf("ERROR: Could not load table\n");
		return false;
	}
	return true;
}

bool loadShaders()
{
	gShaders.resize(SHADER_NB);
	if (!gShaders[SHADER_BASIC].loadProgram("Resources/Shaders/mvp"))
	{
		printf("ERROR: Could not load shader\n");
		return false;
	}
	gShaders[SHADER_BASIC].setMaxUniforms(3);
	gShaders[SHADER_BASIC].addUniform("M");
	gShaders[SHADER_BASIC].addUniform("V");
	gShaders[SHADER_BASIC].addUniform("P");

	/*if (!gShaders[SHADER_BASIC].loadProgram("Resources/Shaders/zone"))
	{
		printf("ERROR: Could not load shader\n");
		return false;
	}
	gShaders[SHADER_BASIC].setMaxUniforms(4);
	gShaders[SHADER_BASIC].addUniform("M");
	gShaders[SHADER_BASIC].addUniform("V");
	gShaders[SHADER_BASIC].addUniform("P");
	gShaders[SHADER_BASIC].addUniform("zoneColor");*/
	return true;
}

bool loadResources()
{
	return (loadTextures() && loadMeshs() && loadShaders());
}