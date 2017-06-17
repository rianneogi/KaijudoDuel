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

glm::vec3 slerp(glm::vec3 v0, glm::vec3 v1, float t) 
{
	// Only unit quaternions are valid rotations.
	// Normalize to avoid undefined behavior.
	glm::normalize(v0);
	glm::normalize(v1);

	// Compute the cosine of the angle between the two vectors.
	float dot = glm::dot(v0, v1);

	const float DOT_THRESHOLD = 0.9995;
	if (fabs(dot) > DOT_THRESHOLD) {
		// If the inputs are too close for comfort, linearly interpolate
		// and normalize the result.

		glm::vec3 result = v0 + t*(v1 - v0);
		glm::normalize(result);
		return result;
	}

	// If the dot product is negative, the quaternions
	// have opposite handed-ness and slerp won't take
	// the shorter path. Fix by reversing one quaternion.
	if (dot < 0.0f) {
		v1 = -v1;
		dot = -dot;
	}

	glm::clamp<float>(dot, -1, 1);           // Robustness: Stay within domain of acos()
	double theta_0 = acos(dot);  // theta_0 = angle between input vectors
	double theta = theta_0*t;    // theta = angle between v0 and result 

	glm::vec3 v2 = v1 - v0*dot;
	glm::normalize(v2);              // { v0, v2 } is now an orthonormal basis

	return v0*float(cos(theta)) + v2*float(sin(theta));
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

