#pragma once

#include "Ray.h"
#include "Camera.h"
#include "Objects/Hittable.h"

class Scene
{
public:
	Scene(const std::filesystem::path& sceneFile);
	~Scene() = default;

	std::shared_ptr<Camera> GetCamera() const { return m_Camera; }

	void Render() const;

private:
	glm::vec3 GetHitColor(const Ray& ray, const HitRecord& hit, uint32_t depth) const;
	glm::vec3 GetBackgroundColor(const glm::vec3& direction) const;
	glm::vec3 CastRay(const Ray& ray, uint32_t depth) const;
	void RenderPart(Image* image, uint32_t fromY, uint32_t toY) const;

private:
	std::shared_ptr<Camera> m_Camera;
	std::vector<std::shared_ptr<Hittable>> m_Objects;
};
