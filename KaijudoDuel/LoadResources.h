#pragma once

#include "Camera.h"

extern Texture gTableTexture;
extern Texture gCardBackTexture;
extern std::vector<Texture*> gCardTextures;

enum MeshEnum { MESH_CARD, MESH_TABLE, MESH_NB };
extern std::vector<Mesh> gMeshs;

enum ShaderEnum { SHADER_BASIC, SHADER_NB };
extern std::vector<ShaderProgram> gShaders;

bool loadResources();