#pragma once

#include "../Ray.h"
#include "../Materials/Material.h"

struct HitRecord
{
	glm::vec3 point;
	glm::vec3 normal;
	std::shared_ptr<Material> material;
	float t;
	bool frontFace;

	inline void SetNormal(const Ray& ray, const glm::vec3& outwardNormal)
	{
		frontFace = dot(ray.GetDirection(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	Hittable(const std::shared_ptr<Material>& material);
	virtual ~Hittable() = default;

	inline std::shared_ptr<Material> GetMaterial() const { return m_Material; }

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hit) const = 0;

protected:
	std::shared_ptr<Material> m_Material;
};
