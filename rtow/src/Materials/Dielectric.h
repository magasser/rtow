#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float refractionIndex) : Material(), m_RefractionIndex(refractionIndex) { }

	bool Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const override;

private:
	float m_RefractionIndex;
};
