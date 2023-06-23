#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(const glm::vec3& center, float radius, const std::shared_ptr<Material>& material)
	: Hittable(material),
	  m_Center(center),
	  m_Radius(radius) {}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hit) const
{
	glm::vec3 oc = ray.GetOrigin() - m_Center;

	float a = glm::length2(ray.GetDirection());
	float hb = glm::dot(oc, ray.GetDirection());
	float c = glm::length2(oc) - m_Radius * m_Radius;

	float discriminant = hb * hb - a * c;

	if (discriminant < 0)
		return false;
	
	float rootD = glm::sqrt(discriminant);

	float root = (-hb - rootD) / a;

	if (root < tMin || root > tMax)
	{
		root = (-hb + rootD) / a;
		if (root < tMin || root > tMax)
			return false;
	}

	hit.t = root;
	hit.point = ray.At(hit.t);
	glm::vec3 outwardNormal = glm::normalize((hit.point - m_Center) / m_Radius);

	hit.SetNormal(ray, outwardNormal);
	hit.material = m_Material;

	return true;
}
