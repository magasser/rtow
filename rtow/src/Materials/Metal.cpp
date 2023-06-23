#include "pch.h"
#include "Metal.h"

#include "../Objects/Hittable.h"

#include "../utils.h"

bool Metal::Scatter(const Ray& ray, const HitRecord& hit, glm::vec3& attenuation, Ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(glm::normalize(ray.GetDirection()), hit.normal);
	scattered = Ray(hit.point, reflected + m_Fuzz * utils::randInUnitSphere());
	attenuation = m_Albedo;
	return glm::dot(scattered.GetDirection(), hit.normal) > 0.0f;
}
