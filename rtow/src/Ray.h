#pragma once

#include <glm/vec3.hpp>

class Ray
{
public:
	Ray() { }

	Ray(const glm::vec3& origin, const glm::vec3& direction);
	~Ray() = default;

	inline const glm::vec3& GetOrigin() const { return m_Origin; }
	inline const glm::vec3& GetDirection() const { return m_Direction; }

	inline glm::vec3 At(float t) const { return m_Origin + m_Direction * t; }

private:
	glm::vec3 m_Origin, m_Direction;
};
