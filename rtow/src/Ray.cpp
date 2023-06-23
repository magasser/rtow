#include "pch.h"
#include "Ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
	: m_Origin(origin), m_Direction(direction) {}
