
#include "hen/util/MathLib.h"

#include <glm/gtc/matrix_transform.hpp>

float hen::math::getAngle(glm::vec3 v1, glm::vec3 v2)
{
	float length = glm::length(v1) * glm::length(v2);
	return (length >= 0.00001f ? 180.0f / PI * acos(glm::dot(v1, v2) / length) : 0.0f);
}
glm::vec3 hen::math::toCartesian(float yaw, float pitch)
{
	pitch *= PI / 180.0f;
	yaw *= PI / 180.0f;
	return glm::vec3(cos(yaw) * cos(pitch), sin(yaw) * cos(pitch), sin(pitch));
}
glm::vec2 hen::math::toSpherical(const glm::vec3& direction)
{
	glm::vec2 rot;
	rot.x = std::atan2(direction.y, direction.x) * 180.0f / PI;
	rot.y = 90.0f - getAngle(glm::vec3(0.0f, 0.0f, 1.0f), direction);
	return rot;
}
