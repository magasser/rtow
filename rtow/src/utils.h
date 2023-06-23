#pragma once

#include <random>
#include <glm/vec3.hpp>

namespace utils
{
	float randFloat();
	float randFloat(float min, float max);
	glm::vec3 randVec3();
	glm::vec3 randVec3(float min, float max);
	glm::vec3 randInUnitSphere();
	glm::vec3 randUnitVec();
	glm::vec3 randInHemisphere(const glm::vec3& normal);
	glm::vec3 randInUnitDisk();
}
