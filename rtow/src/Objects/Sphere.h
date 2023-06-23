#pragma once

#include "Hittable.h"
#include "../Materials/Material.h"

class Sphere : public Hittable
{
public:
	Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material);
	~Sphere() = default;

	inline const glm::vec3& GetCenter() const { return m_Center; }
	inline float GetRadius() const { return m_Radius; }

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hit) const override;

private:
	glm::vec3 m_Center;
	float m_Radius;
};
