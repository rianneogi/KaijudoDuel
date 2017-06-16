#pragma once

#include <SDL.h>
#include <IL\il.h>
#include <IL\ilu.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <vector>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\noise.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>

//#include <gl\GL.h>
//#include <gl\GLU.h>

glm::quat getRotationBetweenVectors(glm::vec3 start, glm::vec3 dest);
int isPointInsidePolygon(std::vector<glm::vec4> points, float x, float y);
bool debugOpengl(std::string errorstring);
