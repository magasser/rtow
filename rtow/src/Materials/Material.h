#pragma once

#include "../Ray.h"

struct HitRecord;

class Material
{
public:
	Material() { }

	Material(const glm::vec3& albedo) : m_Albedo(albedo) { }

	virtual bool Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const = 0;

protected:
	glm::vec3 m_Albedo;
};
