#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& albedo) : Material(albedo) { }

	bool Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const override;
};
