#include "pch.h"
#include "Lambertian.h"

#include "../Objects/Hittable.h"

#include "../utils.h"

bool nearZero(const glm::vec3& v)
{
	static float s = 1e-8;

	return glm::abs(v.x) < s && glm::abs(v.y) < s && glm::abs(v.z) < s;
}

bool Lambertian::Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const
{
	//static float epsilon2 = FLT_EPSILON * FLT_EPSILON;

	glm::vec3 scatterDirection = hit.normal + utils::randUnitVec();

	//if (glm::length2(scatterDirection) < epsilon2)
	if (nearZero(scatterDirection))
		scatterDirection = hit.normal;

	scattered = Ray(hit.point, scatterDirection);
	attenuation = m_Albedo;
	return true;
}
