#pragma once

#include <SDL.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include <gl\glew.h>
#include <SDL_opengl.h>

#include <ft2build.h>
#include <freetype\freetype.h>
#define FT_FREETYPE_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\noise.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

#include <vector>
#include <map>

//#include <gl\GL.h>
//#include <gl\GLU.h>

glm::quat getRotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
int isPointInsidePolygon(std::vector<glm::vec4> points, float x, float y);
glm::vec3 slerp(glm::vec3 v0, glm::vec3 v1, float t);
bool debugOpengl(std::string errorstring);
char* readFile(const char* filename, int* size);