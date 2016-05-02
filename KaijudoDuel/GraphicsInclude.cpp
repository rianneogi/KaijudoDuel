#include "GraphicsInclude.h"

bool debugOpengl(std::string errorstring)
{
	GLenum error = GL_NO_ERROR;
	bool outputOK = true;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		printf("!!ERROR!! %s : %d - %s\n", errorstring.c_str(), error, gluErrorString(error));
		outputOK = false;
	}
	return outputOK;
}

int isPointInsidePolygon(std::vector<glm::vec4> points, float x, float y)
{
	int npol = points.size();
	int i, j, c = 0;
	for (i = 0, j = npol - 1; i < npol; j = i++) {
		if ((((points[i].y <= y) && (y < points[j].y)) ||
			((points[j].y <= y) && (y < points[i].y))) &&
			(x < (points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			c = !c;
	}
	return c;
}

glm::quat getRotationBetweenVectors(glm::vec3 start, glm::vec3 dest) {
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		
		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(float(M_PI), rotationAxis);
	}

	rotationAxis = glm::cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
		);
}