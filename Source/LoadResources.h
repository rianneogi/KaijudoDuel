#pragma once

#include "Movement.h"

extern Texture gTableTexture;
extern Texture gCardBackTexture;
extern std::vector<Texture*> gCardTextures;

enum MeshEnum { MESH_CARD, MESH_TABLE, MESH_ENDTURN, MESH_NB };
extern std::vector<Mesh> gMeshs;

enum ShaderEnum { SHADER_BASIC, SHADER_PHONG, SHADER_NB };
extern std::vector<ShaderProgram> gShaders;

bool loadResources();