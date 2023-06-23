#include "pch.h"
#include "Dielectric.h"

#include "../Objects/Hittable.h"

#include "../utils.h"

// Schlick's approximation
float Reflectance(float cos, float refractionIndex)
{
	float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);

	r0 = r0 * r0;

	return r0 + (1.0f - r0) * glm::pow(1.0f - cos, 5.0f);
}

bool Dielectric::Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const
{
	attenuation = glm::vec3(1.0f);

	float refractionRatio = hit.frontFace ? 1.0f / m_RefractionIndex : m_RefractionIndex;

	glm::vec3 unitDirection = glm::normalize(ray.GetDirection());

	float cosTheta = glm::min(glm::dot(-unitDirection, hit.normal), 1.0f);
	float sinTheta = glm::sqrt(1.0f - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0f;

	glm::vec3 direction = cannotRefract || Reflectance(cosTheta, refractionRatio) > utils::randFloat()
		                      ? glm::reflect(unitDirection, hit.normal)
		                      : glm::refract(unitDirection, hit.normal, refractionRatio);

	scattered = Ray(hit.point, direction);
	return true;
}
