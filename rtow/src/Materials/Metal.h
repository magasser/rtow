#pragma once

#include "Material.h"

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : Material(albedo), m_Fuzz(fuzz) { }

	bool Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const override;

private:
	float m_Fuzz;
};
